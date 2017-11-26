#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "Utils.h"
#include "SD_Interface.h"
#include "GameFSM.h"

#define TFT_CS 10
#define TFT_RST 8 
#define TFT_DC 9

#define SD_CS 4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

using namespace Utils;

GameFSM fsm = GameFSM(&tft);

void setup(void)
{
  Serial.begin(9600);
  while (!Serial)
    ;
  tft.initR(INITR_BLACKTAB);
  Serial.println("TFT initialized");
  tft.fillScreen(ST7735_BLACK);

  // look for SD card
  initialiseSDcard();

  fsm.init();
}

void loop()
{
  fsm.update();
}

void initialiseSDcard()
{
  tft.setCursor(10, 30);
  tft.setTextSize(1);

  if (!SD.begin(SD_CS))
  {
    tft.setTextColor(ST7735_RED);
    tft.println("SD card not found!");
  }
  else
  {
    tft.setTextColor(ST7735_GREEN);
    tft.println("SD card found");
  }
  delay(1000);
  tft.fillScreen(ST7735_BLACK);
}























