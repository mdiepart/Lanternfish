#define FW_VERSION "1.0.0"

#include <LiquidCrystal.h>
#define ENCODER_USE_INTERRUPTS
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Wire.h>

#define RTC_ADD 0b1101111
#define LCD_TIMEOUT 30000
#define LONG_PRESS_DURATION 1000

typedef unsigned short int bcd;

LiquidCrystal lcd(10, 9, 8, A0, 7, 0, A1, 4, 1, A2, A3);
Encoder knob(2, 3);

volatile bool deviceSleeping = false;
volatile unsigned long int lastActivity = 0;
volatile bool swBack = false;
bool swBackStat = 0;
volatile bool swNew = false;
bool swNewStat = 0;
volatile bool swMan = false;
bool swManStat = 0;
volatile bool swSel = false;
char swSelStat = 0;//0 = default state; 1 = short press; 2 = long press

void setup() {
  /* Rot switch :
   *  A = D2 (PD2)
   *  B = D3 (PD3)
   *  PB = / (PCINT6) (PCIE0)
   *  
   *  LCD :
   *  RS = D10
   *  RW = D9
   *  enable = D8
   *  LCD_D0 = A0
   *  LCD_D1 = D7
   *  LCD_D2 = D0
   *  LCD_D3 = A1
   *  LCD_D4 = D4
   *  LCD_D5 = D1
   *  LCD_D6 = A2
   *  LCD_D7 = A3
   *  Backlight = D6
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
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  /* Configures I2C */
  Wire.begin();
  Wire.setClock(400000);

  enableRTC();
  
  /*
   * Enabling PinChangeInterrupt
   */
  PCMSK3 = 0b00000011;
  PCMSK0 = 0b11000000;
  PCIFR = 0;
  PCICR = 0b00001001;
}

volatile char prev_
ISR(PCINT0_vect){
  swMan = PORTB & (1 << PB7);
  swSel = PORTB & (1 << PB6);
  lastActivity = millis();
}

ISR(PCINT3_vect){
  swBack = PORTE & (1 << PE0);
  swNew = PORTE & (1 << PE1);
  lastActivity = millis();
}

void loop() {
  /*
   * Read buttons, knob,...
   * Read rtc every 10 seconds
   * update menu state
   * refresh screen
   */
  long int knobVal = knob.readAndReset();
  if(knobVal != 0){
    lastActivity = millis();
  }
  
  processSwitches();

  /* checks if we have to shutdown LCD */
  if(millis() - lastActivity >= LCD_TIMEOUT){
    digitalWrite(D6, LOW);
  }else{
    digitalWrite(D6, HIGH);
  }



  

}

void processSwitches(){
  static long int selRiseTime = 0;
  static bool selPrevValue = false;
  if(selPrevValue == false && swSel == true){
    //Rising edge
    selRiseTime = millis();    
  }else if(selPrevValue == true && swSel == false){
    //Falling edge
    if(millis()-selRiseTime < LONG_PRESS_DURATION && millis()-selRiseTime > MIN_PRESS_DURATION){
      swSel = 1;
    }
  }else if(millis()-selRiseTime > LONG_PRESS_DURATION){
    swSel = 2;
  }
  selPrevValue = 

  
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
bool setRTCTime(bcd dd, bcd hh, bcd mm){
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
 *  *dd pointer to bcd. Will contain the day of the week after calling the function
 *  *hh pointer to bcd. Will contain the hour after calling the function
 *  *mm pointer to bcd. Will contain the minutes after calling the function
 *  
 *  Returns:
 *  True if successful
 *  False otherwise
 */
bool getRTCTime(bcd *dd, bcd *hh, bcd *mm){
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
      *mm = ((c & 0b01110000)>>4)*10 + (c & 0b00001111);
    }else if(counter == 1){ // Hours
      *hh = ((c & 0b00110000)>>4)*10 + (c & 0b00001111);
    }else if(counter == 2){ // Day of the week
      *dd = (c & 0b00000111);
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
