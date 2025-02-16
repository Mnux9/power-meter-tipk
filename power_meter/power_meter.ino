#include "NotoSans-Bold48.h"
#include "NotoSans-Bold24.h"
#include "NotoSans-Bold15.h"

#define FIRMWARE "fw: 0.1"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_MID NotoSansBold24
#define AA_FONT_LARGE NotoSansBold48

#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include <Wire.h>

#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;

TFT_eSPI    tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft); // Sprite class needs to be invoked

void setup(void) {
  pinMode(PC13, OUTPUT);
  delay(100);
  digitalWrite(PC13, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(PC13, LOW);   // turn the LED off by making the voltage LOW
  delay(100);

  Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();
 

  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) {
      digitalWrite(PC13, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(100);                      // wait for a second
      digitalWrite(PC13, LOW);
    }
  }

  //Serial.begin(250000);

  tft.begin();
  tft.setRotation(1);
  spr.setColorDepth(16); // 16-bit colour needed to show anti-aliased fonts
  tft.fillScreen(TFT_NAVY);// Clear screen

  delay(200);
  pinMode(PB9,OUTPUT);
  analogWrite(PB9, 256); 

  spr.loadFont(AA_FONT_LARGE); // Load another different font
  spr.setTextColor(TFT_WHITE, TFT_NAVY);
  tft.setCursor(47, 20); 
  spr.printToSprite("mnux.xyz");

  spr.setTextColor(TFT_WHITE, TFT_NAVY);
  spr.unloadFont();

  spr.loadFont(AA_FONT_MID);
  tft.setCursor(48, 60);
  spr.printToSprite("instruments");

  tft.setCursor(64, 110);
  spr.printToSprite("DC power meter");
  
  spr.loadFont(AA_FONT_MID);
  tft.setCursor(3, 145);
  spr.setTextColor(TFT_DARKGREY, TFT_NAVY);
  spr.printToSprite(FIRMWARE);

  spr.unloadFont();
  delay(2500);

  tft.fillScreen(TFT_NAVY);// Clear screen

  spr.loadFont(AA_FONT_MID);
  tft.setCursor(3, 145);
  spr.setTextColor(TFT_DARKGREY, TFT_NAVY);
  spr.printToSprite("remote");

  spr.setTextColor(TFT_ORANGE, TFT_NAVY);
  spr.loadFont(AA_FONT_LARGE);
  tft.setCursor(220, 1);
  spr.printToSprite("mW");
  tft.setCursor(220, 46);
  spr.printToSprite("mA");
  tft.setCursor(220, 92);
  spr.printToSprite("V");

}

void loop() {
    //tft.setTextSize(8);
    tft.setCursor(0, 1);

    spr.printToSprite(" " + (String) (ina219.getPower_mW()) + " ");
    tft.setCursor(0, 46);
    spr.printToSprite(" " + (String) (ina219.getCurrent_mA()) + " ");
    tft.setCursor(0, 92);
    spr.printToSprite(" " + (String) (ina219.getBusVoltage_V()) + " ");
    //delay (20);

  //spr.unloadFont(); // Remove the font to recover memory used
}
