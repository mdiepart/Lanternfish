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

enum menuState : char {SETTINGS, TIME, TIME_HH, TIME_MM, DAY, DAY_DD, RESET,
                      RESET_CONFIRM, SCHEDULE, MON, TUE, WED, THU, FRI, SAT,
                      SUN, PT_SEL, PT_EDIT, PT_DEL, PT_DEL_CONF, PT_NEW,
                      PT_NEW_HH, PT_NEW_MM, PT_NEW_DC};

menuState menu = SETTINGS;                       

unsigned char timeH = 0;
unsigned char timeM = 0;
unsigned char dow = 0;

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

  char line1[17];
  char line2[17];
  signed char counter = 0;
  /*
   * Menu state machine
   */
  switch(menu){
    case SETTINGS:
      if(knobVal != 0){
        menu = SCHEDULE;
      }else if(swSel == SEL_SHORT){
        menu = TIME;
      }
      line1[0]='\0';
      sprintf(line2,STR_SETTINGS);
      break;
    case TIME:
      if(knobVal > 0){
        menu = DAY;
      }else if(knobVal < 0){
        menu = RESET;
      }else if(swSel == SEL_SHORT){
        menu = TIME_HH;
        counter = timeH;
      }else if(swBack){
        menu = SETTINGS;
      }
      sprintf(line1, STR_SETTINGS);
      sprintf(line2, STR_TIME);
      break;
    case TIME_HH:
      if(knobVal != 0){
        counter = (counter + knobVal + 120)%24;
      }else if(swSel == SEL_SHORT){
        if(setRTCTime(dow, counter, timeM) == true){
          timeH = counter;
        }
        menu = TIME_MM;
        counter = timeM;
      }else if(swBack == true){
        menu = TIME;
      }
      sprintf(line1, STR_TIME);
      sprintf(line2, "%hdh", counter);
      break;
    case TIME_MM:
      if(knobVal != 0){
        counter = (counter + knobVal + 120)%60;
      }else if(swSel == SEL_SHORT){
        if(setRTCTime(dow, timeH, counter) == true){
          timeM = counter;
        }
        menu = TIME;
      }else if(swBack == true){
        menu = TIME;
      }
      sprintf(line1, STR_TIME);
      sprintf(line2, "%hdmin", counter);
      break;
    case DAY:
      if(knobVal > 0){
        menu = RESET;
      }else if(knobVal < 0){
        menu = TIME;
      }else if(swSel == SEL_SHORT){
        menu = DAY_DD;
        counter = dow;
      }else if(swBack){
        menu = SETTINGS;
      }
      sprintf(line1, STR_SETTINGS);
      sprintf(line2, STR_DAY);
      break;
    case DAY_DD:
      if(knobVal != 0){
        counter = (counter + knobval + 70)%7;
      }else if(swSel == SEL_SHORT){
        if(setRTCTime(counter, timeH, timeM)){
          dow = counter;
        }
        menu = DAY;
      }else if(swBack == true){
        menu = DAY;
      }
      sprintf(line1, STR_DAY);
      switch(counter){
        case MONDAY:
          sprintf(line2, "%s", STR_MON);
          break;
        case TUESDAY:
          sprintf(line2, "%s", STR_TUE);
          break;
        case WEDNESDAY:
          sprintf(line2, "%s", STR_WED);
          break;
        case THURSDAY:
          sprintf(line2, "%s", STR_THU);
          break;
        case FRIDAY:
          sprintf(line2, "%s", STR_FRI);
          break;
        case SATURDAY:
          sprintf(line2, "%s", STR_SAT);
          break;
        case SUNDAY:
          sprintf(line2, "%s", STR_SUN);
          break;
        default:
          sprintf(line2, "%s", STR_ERROR);
          break;
      }
      break;
    case RESET:
      if(knobVal < 0){
        menu = DAY;
      }else if(knobVal > 0){
        menu = TIME;
      }else if(swSel == SEL_SHORT){
        menu = RESET_CONFIRM;
        counter = dow;
      }else if(swBack){
        menu = SETTINGS;
      }
      sprintf(line1, STR_SETTINGS);
      sprintf(line2, "%s?", STR_RESET);
      break;
    case RESET_CONFIRM:
    
      break;
    case SCHEDULE:
      break;
    case MON:
      break;
    case TUE:
      break;
    case WED:
      break;
    case THU:
      break;
    case FRI:
      break;
    case SAT:
      break;
    case SUN:
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
