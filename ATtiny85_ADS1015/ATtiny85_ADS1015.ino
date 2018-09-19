//https://www.instructables.com/id/Using-an-I2C-LCD-on-Attiny85/

/* ATtiny85 as an I2C Master
 * Modified for Digistump
 * SETUP:
 * ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) N/U
 * ATtiny Pin 3 = (D4) N/U                         ATtiny Pin 4 = GND
 * ATtiny Pin 5 = (D0) SDA on DS1621  & GPIO       ATtiny Pin 6 = (D1) to LED2
 * ATtiny Pin 7 = (D2) SCK on DS1621  & GPIO       ATtiny Pin 8 = VCC (2.7-5.5V)
 * LiquidCrystal_I2C lib was modified for ATtiny - on Playground with TinyWireM lib.
 * TinyWireM USAGE & CREDITS: - see TinyWireM.h
 */

#include <TinyWireM.h>              //I2C lib
#include <LiquidCrystal_I2C.h>      //LCD lib
#include "Adafruit_ADS1015.h"

#define LCD_I2C_ADD 0x3F
Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

LiquidCrystal_I2C lcd(LCD_I2C_ADD,16,2);  // set address & 16 chars / 2 lines
char outputA0[8];
int16_t adc0;

void setup()
{
  TinyWireM.begin();                    // initialize I2C lib

  lcd.init();                           // initialize the lcd 
  lcd.backlight(); 
  lcd.clear();  // Print a message to the LCD.
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  ads.begin();
  delay(3000);
}

void loop()
{
  //adc0 = ads.readADC_SingleEnded(0);
  adc0 = ads.readADC_Differential_2_3();
  sprintf(outputA0, "%04.02d", adc0);
  lcd.setCursor(0, 0);
  lcd.print(outputA0);
  delay(10);
}
