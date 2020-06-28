#define FW_VERSION "1.0.0"

#include <LiquidCrystal.h>
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>



LiquidCrystal lcd(D10, D9, D8, A0, D7, D0, A1, D4, D1, A2, A3);
Encoder knob(D2, D3);

void setup() {
  /* Rot switch :
   *  A = D2 (PD2)
   *  B = D3 (PD3)
   *  PB = / (PCINT6)
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
   *  BACK (1) = / (PCINT24)
   *  NEW (2) = / (PCINT25)
   *  
   *  Output :
   *  Gate = D5
   *  
   *  RTC : 1101111+(R/~W)
   *  I2C
   *  MSP = PE2 (PCINT26)
   */
   lcd.begin(16, 2);
   lcd.write("Lanternfish");
   lcd.setCursor(0, 1);
   lcd.write(FW_VERSION);

   pinMode(D5, OUTPUT);
   pinMode(D6, OUTPUT);
}

void loop() {

  /*
   * Read buttons, knob,...
   * Read rtc every 10 seconds
   * update menu state
   * refresh screen
   */

}
