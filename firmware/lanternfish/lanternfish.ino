
/*
 * ATMega 328PB
 * Clock @ 8MHz (Internal)
 * UART0
 * BOD @ 2.7V
 */

#define FW_VERSION "1.0.0"
#define ENGLISH
#include <LiquidCrystal.h>
#define ENCODER_USE_INTERRUPTS
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Wire.h>
#include <String.h>
#include "strings.h"
#include "daySchedule.h"

#define RTC_ADD 0b1101111         
#define LCD_TIMEOUT 30000         //30_000ms = 30s
#define LONG_PRESS_DURATION 1000  //1000ms = 1s
#define MIN_PRESS_DURATION 50     //50 ms
#define RTC_UPDATE_INTERVAL 10000 //10_000ms = 10s
#define SEL_SHORT 1
#define SEL_LONG 2

typedef unsigned short int bcd;

LiquidCrystal lcd(PIN_PB2, PIN_PB1, PIN_PB0, PIN_PC0, PIN_PD7, PIN_PD0, PIN_PC1,
                  PIN_PD4, PIN_PD1, PIN_PC2, PIN_PC3);
Encoder knob(PIN_PD2, PIN_PD3);

DaySchedule schedule(0);

volatile bool deviceSleeping = false;
volatile unsigned long int lastActivity = 0;
volatile bool swBackStat = 0;
volatile bool swNewStat = 0;
volatile bool swManStat = 0; //false = prog mode, true = man mode
volatile char swSelStat = 0; //0 = default state; 1 = short press; 2 = long press

enum menuFSM : char {SETTINGS, TIME, TIME_HH, TIME_MM, DAY, DAY_DD, RESET,
                      RESET_CONFIRM, SCHEDULE, MON, TUE, WED, THU, FRI, SAT,
                      SUN, PT_SEL, PT_EDIT, PT_DEL, PT_DEL_CONF, PT_NEW,
                      PT_NEW_HH, PT_NEW_MM, PT_NEW_DC};


typedef struct{
  //Finite state machine
  menuFSM fsm = SCHEDULE;
  
  //Schedule used for edition
  DaySchedule editionSchedule = DaySchedule(MONDAY);
  
  //To pass values
  union{
    unsigned char counter = 0;
    unsigned char mm;
    unsigned char hh;
    unsigned char dd;
    unsigned char dc; //duty cycle
  };
  unsigned char daySelected = MONDAY;
  unsigned char point = 0;
  point schedulePoint = point();
  
  
} menuState;

unsigned char _timeH = 0;
unsigned char _timeM = 0;
unsigned char _dow = 0;

void setup() {
  /* Rot switch :
   *  A = D2 (PD2)
   *  B = D3 (PD3)
   *  PB = / (PCINT6) (PCIE0)
   *  
   *  LCD :
   *  RS = D10 = PB2
   *  RW = D9 = PB1
   *  enable = D8 = PB0
   *  LCD_D0 = A0 = PC0
   *  LCD_D1 = D7 = PD7
   *  LCD_D2 = D0 = PD0
   *  LCD_D3 = A1 = PC1
   *  LCD_D4 = D4 = PD4
   *  LCD_D5 = D1 = PD1
   *  LCD_D6 = A2 = PC2
   *  LCD_D7 = A3 = PC3
   *  Backlight = D6 = PD6
   *  
   *  Switches :
   *  BACK (1) = / (PCINT24) (PCIE3)
   *  NEW (2) = / (PCINT25) (PCIE3)
   *  MAN     = / (PCINT7) (PCIE0)
   *  
   *  Output :
   *  Gate = D5
   *  
   *  RTC : 1101111+(R/~W)
   *  I2C
   *  MSP = PE2 (PCINT26)
   */

  /*Configures LCD*/
  lcd.begin(16, 2);
  lcd.write("Lanternfish");
  lcd.setCursor(0, 1);
  lcd.write(FW_VERSION);
   
  /* Configures pins */
  pinMode(PIN_PD5, OUTPUT); // Gate
  pinMode(PIN_PD6, OUTPUT); // LCD Backlight

  /* Configures I2C */
  Wire.begin();
  Wire.setClock(400000);

  enableRTC();

  //Fetch the time from the RTC
  if(!getRTCTime(dow, timeH, timeM)){
    //There was an error fetching time from the RTC.
    lcd.setCursor(0, 0);
    lcd.write("RTC ERROR");
    while(true){}
  }

  // Load data points for today
  schedule.changeDay(dow);
  
  /*
   * Enabling PinChangeInterrupt
   */
  PCMSK3 = 0b00000011;
  PCMSK0 = 0b11000000;
  PCIFR = 0;
  PCICR = 0b00001001;
}

ISR(PCINT0_vect){
  bool swMan = (PORTB & (1 << PB7)) != 0;
  bool swSel = (PORTB & (1 << PB6)) != 0;
  lastActivity = millis();

  /*
   * Sel switch (knob press switch) 
   * Sets the status of the switch only after it is release
   * to be able to distinguish between long and short presses
   */
  static long int selFallTime = 0;
  static bool selPrevValue = true;
  if(selPrevValue && !swSel){
    //Falling edge
    selFallTime = millis();    
  }else if(!selPrevValue && swSel){
    //Rising edge
    if( (millis()-selFallTime < LONG_PRESS_DURATION) &&
        (millis()-selFallTime > MIN_PRESS_DURATION) ){
      swSelStat = SEL_SHORT; //Short press
    }
  }else if(!swSel &&
            (millis()-selFallTime > LONG_PRESS_DURATION)){
    swSelStat = SEL_LONG; //Long press
  }
  selPrevValue = swSel;

  /*
   * "Man" switch
   * Sets the status of the switch as fast as possible.
   * This is a toggle switch.
   */
  static long int manFallTime = 0;
  static long int manRiseTime = 0;
  static bool manPrevValue = true;
  if(manPrevValue && !swMan){
    //Falling edge
    manFallTime = millis();    
  }else if(!manPrevValue && swMan){
    //Rising edge
    manRiseTime = millis();
  }
  if(swMan && (millis()-manRiseTime > MIN_PRESS_DURATION) ){
    swManStat = false; //prog mode
  }else if(swMan && (millis()-manFallTime > MIN_PRESS_DURATION) ){
    swManStat = true; //man mode 
  }

  manPrevValue = swMan;
   
}

ISR(PCINT3_vect){
  bool swBack = (PORTE & (1 << PE0)) != 0;
  bool swNew = (PORTE & (1 << PE1)) != 0;
  lastActivity = millis();

  /*
   * "Back" switch
   * Sets the status of the switch as fast as possible.
   * We do not have to distinguish between long and short presses.
   */
  static long int backFallTime = 0;
  static bool backPrevValue = false;
  if(backPrevValue && !swBack){
    //Falling edge
    backFallTime = millis();
  }
  if(!swBack &&
      (millis()-backFallTime > MIN_PRESS_DURATION) ){
    swBackStat = true;
  }
  backPrevValue = swBack;

  /*
   * "New" switch
   * Sets the status of the switch as fast as possible.
   * We do not have to distinguish between long and short presses.
   */
  static long int newFallTime = 0;
  static bool newPrevValue = false;
  if(newPrevValue && !swNew){
    //Falling edge
    newFallTime = millis();
  }
  if(!swNew &&
      (millis()-newFallTime > MIN_PRESS_DURATION) ){
    swNewStat = true;
  }
  newPrevValue = swNew;
  
}

void loop() {
  /*
   * Read buttons, knob,...
   * Read rtc every 10 seconds
   * update menu state
   * refresh screen
   */
  long int knobVal = knob.read(); knob.write(0);
  static long unsigned int lastRTCRead = 0;
  static unsigned short int prevDow = dow;

  //Check if we have to fetch time from RTC
  if(millis() - lastRTCRead > RTC_UPDATE_INTERVAL){
    if(getRTCTime(dow, timeH, timeM) == true){
      lastRTCRead = millis();  
    }
    if(dow != prevDow){
      schedule.changeDay(dow);
      prevDow = dow;
    }
  }

  
  if(knobVal != 0){
    lastActivity = millis();
  }
  
  /* checks if we have to shutdown LCD */
  if(millis() - lastActivity >= LCD_TIMEOUT){
    digitalWrite(PIN_PD6, LOW);
  }else{
    digitalWrite(PIN_PD6, HIGH);
  }
  
  updateMenu(knobVal, swSelStat, swBackStat, swNewStat);
}

/*
 * Sets the time on the MCP7940M RTC clock.
 * 
 * Parameters :
 * dd = day. 1 <= dd <= 7 (1 = Monday; 7 = Sunday)
 * hh = hour. 0 <= hh < 24
 * mm = minutes. 0 <= mm < 60
 * 
 * Returns:
 * True if successful 
 * False otherwise
 */
bool setRTCTime(const uint8_t dd, const uint8_t hh, const uint8_t mm){
  if(dd >= 7 || hh >= 24 || mm >= 60){
    return false;
  }
  Wire.beginTransmission(RTC_ADD);
  Wire.write(0x01); //minutes register
  char minutes = (mm/10)<<4 & (mm%10);
  Wire.write(minutes);
  char hours = (hh/10)<<4 & (hh%10) & 0b00111111; //Hour + 12/~24
  Wire.write(hours);
  Wire.write(dd & 0b00000111);
  Wire.endTransmission();  
}

/*
 * Querries the time (Day of the weeh, hour and minutes) from the RTC module.
 *  *dd pointer to bcd. Will contain the day of the week after the call
 *  *hh pointer to bcd. Will contain the hour after the call
 *  *mm pointer to bcd. Will contain the minutes after the call
 *  
 *  Returns:
 *  True if successful
 *  False otherwise
 */
bool getRTCTime(uint8_t &dd, uint8_t &hh, uint8_t &mm){
  /* Set address pointer to 0x01 */
  Wire.beginTransmission(RTC_ADD);
  Wire.write(0x01);
  Wire.endTransmission();

  /* Read 3 bytes */
  Wire.requestFrom(RTC_ADD, 3, 1);
  short int counter = 0;
  while(Wire.available()){
    char c = Wire.read();
    if(counter == 0){ //Minutes
      mm = ((c & 0b01110000)>>4)*10 + (c & 0b00001111);
    }else if(counter == 1){ // Hours
      hh = ((c & 0b00110000)>>4)*10 + (c & 0b00001111);
    }else if(counter == 2){ // Day of the week
      dd = (c & 0b00000111);
    }
    counter++;
  }
}

/*
 * Enables the RTC module by setting the ST bit (0x00) to 1 
 * 
 * Returns:
 * true if RTC was enabled properly
 * false if a problem was encountered
 */
bool enableRTC(){
  char stat = 0;
  /*Read address 0x00)*/
  Wire.beginTransmission(RTC_ADD);
  Wire.write(0x00);
  stat &= Wire.endTransmission();
  Wire.requestFrom(RTC_ADD, 1, 0);
  char c;
  if(Wire.available()){
    c = Wire.read();
  }
  c |= 0b100000000; //Sets ST to 1 to enable clock

  /*Write modified byte*/
  Wire.write(0x00);
  Wire.write(c);
  stat &= Wire.endTransmission();

  if(stat != 0){
    return false;
  }
  return true;
}

void updateMenu(const long int knobVal, const char swSel, const bool swBack, const bool swNew){
  // Check if multiple button where pressed at once. We cannot manage  
  // that case and return
  if( ((knobVal != 0) && (swSel != 0)) ||
      ((knobVal != 0) && (swBack!= 0)) ||
      ((knobVal != 0) && (swNew != 0)) ||
      ((swSel != 0) && (swBack != 0)) ||
      ((swSel != 0) && (swNew != 0)) ||
      ((swBack != 0) && (swNew != 0)) ){
        return;
      }
  static menuState menu{SCHEDULE, DaySchedule(0), 0, 0};

  updateMenuState(menu, knobVal, swSel, swBack, swNew);
  
  if(menu.updateSchedule == true){
      menu.updateSchedule = false;
  }
  String line1;
  String line2;


  switch(fsm){
    case SETTINGS:
      line1 ="";
      line2 = STR_SETTINGS;
      break;
    case TIME:
      line1 = STR_SETTINGS;
      line2 = STR_TIME;
      break;
    case TIME_HH:
      line1 = STR_TIME;
      line2 = String(menu.hh) + "h";
      //sprintf(line2, "%hdh", counter);
      break;
    case TIME_MM:
      line1 = STR_TIME;
      line2 = String(menu.mm) + "min";
      //sprintf(line2, "%hdmin", counter);
      break;
    case DAY:
      line1 = STR_SETTINGS;
      line2 = STR_DAY;
      break;
    case DAY_DD:
      line1 = STR_DAY;
      switch(menu.dd){
        case MONDAY:
          line2 = STR_MON;
          break;
        case TUESDAY:
          line2 = STR_TUE;
          break;
        case WEDNESDAY:
          line2 = STR_WED;
          break;
        case THURSDAY:
          line2 = STR_THU;
          break;
        case FRIDAY:
          line2 = STR_FRI;
          break;
        case SATURDAY:
          line2 = STR_SAT;
          break;
        case SUNDAY:
          line2 = STR_SUN;
          break;
        default:
          line2 = STR_ERROR;
          break;
      }
      break;
    case RESET:
      line1 = STR_SETTINGS;
      line2 = String(STR_RESET) + "?";
      break;
    case RESET_CONFIRM:
      line1 = STR_CONF;
      line2 = STR_LP_CONF;
      break;    
    case SCHEDULE:
      line1 ="";
      line2 = STR_SCHEDULE;
      break;
    case MON:
      line1 = "";
      line2 = STR_MON;
      break;
    case TUE:
      line1 = "";
      line2 = STR_TUE;
      break;
    case WED:
      line1 = "";
      line2 = STR_WED;
      break;
    case THU:
      line1 = "";
      line2 = STR_THU;
      break;
    case FRI:
      line1 = "";
      line2 = STR_FRI;
      break;
    case SAT:
      line1 = "";
      line2 = STR_SAT;
      break;
    case SUN:
      line1 = "";
      line2 = STR_SUN;
      break;
    case PT_SEL:
      break;
    case PT_EDIT:
      break;
    case PT_DEL:
      break;
    case PT_DEL_CONF:
      break;
    case PT_NEW:
      break;
    case PT_NEW_HH:
      break;
    case PT_NEW_MM:
      break;
    case PT_NEW_DC:
      break;
  }
}

void updateMenuFSM(menuState &menuState, const long int knobVal, const char swSel, const bool swBack, const bool swNew){
  // Check if multiple button where pressed at once. We cannot manage  
  // that case and return
  if( ((knobVal != 0) && (swSel != 0)) ||
      ((knobVal != 0) && (swBack!= 0)) ||
      ((knobVal != 0) && (swNew != 0)) ||
      ((swSel != 0) && (swBack != 0)) ||
      ((swSel != 0) && (swNew != 0)) ||
      ((swBack != 0) && (swNew != 0)) ){
        return;
      }
  
  /*
   * Menu state machine
   */
  switch(menu.fsm){
    case SETTINGS:
      if(knobVal != 0){
        menu.fsm = SCHEDULE;
      }else if(swSel == SEL_SHORT){
        menu.fsm = TIME;
      }
      break;
    case TIME:
      if(knobVal > 0){
        menu.fsm = DAY;
      }else if(knobVal < 0){
        menu.fsm = RESET;
      }else if(swSel == SEL_SHORT){
        menu.hh = _timeH;
        menu.fsm = TIME_HH;
      }else if(swBack){
        menu.fsm = SETTINGS;
      }
      break;
    case TIME_HH:
      if(knobVal != 0){
        menu.hh = (knobVal + menu.hh + 120)%24;
      }else if(swSel == SEL_SHORT){
        if(setRTCTime(_dow, menu.hh, _timeM) == true){
          _timeH = menu.hh;
        }
        menu.mm = _timeM;
        menu.fsm = TIME_MM;
      }
      break;
    case TIME_MM:
      if(knobVal != 0){
        menu.mm = (knobVal + menu.mm + 120)%60;
      }else if(swSel == SEL_SHORT){
        if(setRTCTime(_dow, _timeH, menu.mm) == true){
          _timeM = menu.mm;
        }
        menu.fsm = TIME;
      }
      break;
    case DAY:
      if(knobVal > 0){
        menu.fsm = RESET;
      }else if(knobVal < 0){
        menu.fsm = TIME;
      }else if(swSel == SEL_SHORT){
        menu.fsm = DAY_DD;
        menu.dd = _dow;
      }else if(swBack){
        menu.fsm = SETTINGS;
      }
      break;
    case DAY_DD:
      if(knobVal != 0){
        menu.dd = (knobVal + menu.dd + 70)%7;
      }else if(swSel == SEL_SHORT){
        if(setRTCTime(menu.dd, _timeH, _timeM)){
          _dow = menu.dd;
        }
        menu.fsm = DAY;
      }else if(swBack == true){
        menu.fsm = DAY;
      }
      switch(counter){
        case MONDAY:
          line2 = STR_MON;
          break;
        case TUESDAY:
          line2 = STR_TUE;
          break;
        case WEDNESDAY:
          line2 = STR_WED;
          break;
        case THURSDAY:
          line2 = STR_THU;
          break;
        case FRIDAY:
          line2 = STR_FRI;
          break;
        case SATURDAY:
          line2 = STR_SAT;
          break;
        case SUNDAY:
          line2 = STR_SUN;
          break;
        default:
          line2 = STR_ERROR;
          break;
      }
      break;
    case RESET:
      if(knobVal < 0){
        menu.fsm = DAY;
      }else if(knobVal > 0){
        menu.fsm = TIME;
      }else if(swSel == SEL_SHORT){
        menu.fsm = RESET_CONFIRM;
      }else if(swBack){
        menu.fsm = SETTINGS;
      }
      break;
    case RESET_CONFIRM:
      if(swSel == SEL_LONG){
        for(unsigned char i = 0; i <= 6; i++){
          schedule.changeDay(i);
          schedule.reset();
          schedule.save();
        }
        menu.fsm = SCHEDULE;
      }else if(swBack == true){
        menu.fsm = RESET;
      }
      break;
    case SCHEDULE:
      if(knobVal != 0){
        menu.fsm = SETTINGS;
      }else if(swSel == SEL_SHORT){
        switch(_dow){
          case MONDAY:
            menu.fsm = MON;
            break;
          case TUESDAY:
            menu.fsm = TUE;
            break;
          case WEDNESDAY:
            menu.fsm = WED;
            break;
          case THURSDAY:
            menu.fsm = THU;
            break;
          case FRIDAY:
            menu.fsm = FRI;
            break;
          case SATURDAY:
            menu.fsm = SAT;
            break;
          case SUNDAY:
            menu.fsm = SUN;
            break;
          default:
            menu.fsm = MON;
            break;
        }
      }
      break;
    case MON:
      if(knobVal > 0){
        menu.fsm = TUE;
      }else if(knobVal < 0){
        menu.fsm = SUN;
    }else if(swSel == SEL_SHORT){
        menu.editionSchedule.changeDay(MONDAY);
        menu.fsm = PT_SEL;
      }else if(swBack){
        menu.fsm = SCHEDULE;
      }
      break;
    case TUE:
      if(knobVal > 0){
        menu.fsm = WED;
      }else if(knobVal < 0){
        menu.fsm = MON;
    }else if(swSel == SEL_SHORT){
        menu.editionSchedule.changeDay(TUESDAY);
        menu.fsm = PT_SEL;
      }else if(swBack){
        menu.fsm = SCHEDULE;
      }
      break;
    case WED:
      if(knobVal > 0){
        menu.fsm = THU;
      }else if(knobVal < 0){
        menu.fsm = TUE;
    }else if(swSel == SEL_SHORT){
        menu.editionSchedule.changeDay(WEDNESDAY);
        menu.fsm = PT_SEL;
      }else if(swBack){
        menu.fsm = SCHEDULE;
      }
      break;
    case THU:
      if(knobVal > 0){
        menu.fsm = FRI;
      }else if(knobVal < 0){
        menu.fsm = WED;
    }else if(swSel == SEL_SHORT){
        menu.editionSchedule.changeDay(THURSDAY);
        menu.fsm = PT_SEL;
      }else if(swBack){
        menu.fsm = SCHEDULE;
      }
      break;
    case FRI:
      if(knobVal > 0){
        menu.fsm = SAT;
      }else if(knobVal < 0){
        menu.fsm = THU;
    }else if(swSel == SEL_SHORT){
        menu.editionSchedule.changeDay(FRIDAY);
        menu.fsm = PT_SEL;
      }else if(swBack){
        menu.fsm = SCHEDULE;
      }
      break;
    case SAT:
      if(knobVal > 0){
        menu.fsm = SUN;
      }else if(knobVal < 0){
        menu.fsm = FRI;
    }else if(swSel == SEL_SHORT){
        menu.editionSchedule.changeDay(SATURDAY);
        menu.fsm = PT_SEL;
      }else if(swBack){
        menu.fsm = SCHEDULE;
      }
      break;
    case SUN:
      if(knobVal > 0){
        menu.fsm = MON;
      }else if(knobVal < 0){
        menu.fsm = SAT;
    }else if(swSel == SEL_SHORT){
        menu.editionSchedule.changeDay(SUNDAY);
        menu.point = 0;
        menu.fsm = PT_SEL;
      }else if(swBack){
        menu.fsm = SCHEDULE;
      }
      break;
    case PT_SEL:
      if(knobVal != 0){
        menu.point = (knobVal + menu.point + 70)%editionSchedule.getSize();
    }else if(swSel == SEL_SHORT){
        menu.schedulePoint = editionSchedule.getPoint(menu.point);
        menu.dc = menu.schedulePoint.dc;
        menu.fsm = PT_EDIT;
    }else if(swSel == SEL_LONG){
        menu.fsm =  PT_DEL;
    }else if(swBack){
        switch(menu.daySelected){
          case MONDAY:
            menu.fsm = MON;
            break;
          case TUESDAY:
            menu.fsm = TUE;
            break;
          case WEDNESDAY:
            menu.fsm = WED;
            break;
          case THURSDAY:
            menu.fsm = THU;
            break;
          case FRIDAY:
            menu.fsm = FRI;
            break;
          case SATURDAY:
            menu.fsm = SAT;
            break;
          case SUNDAY:
            menu.fsm = SUN;
            break;
          default:
            menu.fsm = MON;
            break;
        } 
    }else if(swNew){
        menu.fsm = PT_NEW;
    }
      break;
    case PT_EDIT:
      if(knobval != 0){
          menu.dc = (knobVal + menu.dc + 101)%101;
      }else if(swSel == SEL_SHORT){
          menu.schedulePoint.dc = menu.dc;
          menu.editionSchedule.delPoint(menu.point);
          menu.editionSchedule.addPoint(menu.schedulePoint);
          menu.editionSchedule.save();
      }else if(swBack){
          menu.fsm = PT_SEL;
      }
      break;
    case PT_DEL:
      if(swSel == SEL_SHORT){
          menu.fsm = PT_DEL_CONF;
      }else if(swBack){
          menu.fsm = PT_SEL;
      }
      break;
    case PT_DEL_CONF:
      if(swBack){
          menu.fsm = PT_SEL;
      }else if(swSel == SEL_SHORT){
          menu.editionSchedule.delPoint(menu.point);
          menu.editionSchedule.save();
      }
      break;
    case PT_NEW:
        //TODO manage case where schedule is already full.
      if(swSel == SEL_SHORT){
          menu.hh = 0;
          menu.fsm = PT_NEW_HH;
      }else if(swBack){
          menu.fsm = PT_SEL;
      }
      break;
    case PT_NEW_HH:
      if(knobVal != 0){
          menu.hh = (knobVal + menu.hh + 120)%24;
      }else if(swSel == SEL_SHORT){
          menu.schedulePoint.hh = menu.hh;
          menu.mm = 0;
          menu.fsm = PT_NEW_MM;
      }else if(swBack){
          menu.fsm = PT_SEL;
      }
      break;
    case PT_NEW_MM:
      if(knobVal != 0){
          menu.mm = (knobVal + menu.mm + 120)%60;
      }else if(swSel == SEL_SHORT){
          menu.schedulePoint.mm = menu.mm;
          menu.dc = 0;
          menu.fsm = PT_NEW_DC;
      }else if(swBack){
          menu.fsm = PT_SEL;
      }
      break;
    case PT_NEW_DC:
      if(knobVal != 0){
        menu.dc = (knobVal + menu.dc + 101)%101;
      }else if(swSel == SEL_SHORT){
        menu.schedulePoint.dc = menu.dc;
        menu.editionSchedule.addPoint(menu.schedulePoint);
        menu.editionSchedule.save();
        menu.fsm = PT_SEL;
      }else if(swBack){
        menu.fsm = PT_SEL;
      }
      break;
  }
}
