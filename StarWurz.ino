#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "Utils.h"
#include "SD_Interface.h"
#include "GameFSM.h"

#define TFT_CS 10
#define TFT_RST 8 // you can also connect this to the Arduino reset \
  // in which case, set this #define pin to 0!
#define TFT_DC 9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

using namespace Utils;


GameFSM fsm = GameFSM(&tft);

void initialiseSDcard()
{
    tft.setCursor(10, 30);
    tft.setTextSize(1);

    if (!SD_Interface::initCard())
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

void setup(void)
{
    Serial.begin(9600);
    while (!Serial)
        ;
    tft.initR(INITR_BLACKTAB);
    Serial.println("Initialized");
    tft.fillScreen(ST7735_BLACK);

    // look for SD card
    initialiseSDcard();

    // check if scores are available
    loadHighScores();

    //tftPrintTest();
    // a single pixel
    tft.drawPixel(tft.width() / 2, tft.height() / 2, ST7735_GREEN);
    testfastlines(ST7735_RED, ST7735_BLUE);

    tft.fillScreen(ST7735_BLACK);

    fsm.init();

    
}

void loop()
{
    fsm.update();
    
}

void loadHighScores()
{
    int *scores = new int[4]{0};
    const String filepath = "scores.txt";
    int scoreCount = 4;
    if (!SD_Interface::loadScores(scores, scoreCount))
    {
        return;
    }
    for (int i = 0; i < scoreCount; i++)
    {
        Serial.print(scores[i]);
        Serial.print(" ");
    }
    Serial.println();
    delete[] scores;
}



void testlines(uint16_t color)
{
    tft.fillScreen(ST7735_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawLine(0, 0, x, tft.height() - 1, color);
    }
    for (int16_t y = 0; y < tft.height(); y += 6)
    {
        tft.drawLine(0, 0, tft.width() - 1, y, color);
    }

    tft.fillScreen(ST7735_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    }
    for (int16_t y = 0; y < tft.height(); y += 6)
    {
        tft.drawLine(tft.width() - 1, 0, 0, y, color);
    }

    tft.fillScreen(ST7735_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawLine(0, tft.height() - 1, x, 0, color);
    }
    for (int16_t y = 0; y < tft.height(); y += 6)
    {
        tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    }

    tft.fillScreen(ST7735_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    }
    for (int16_t y = 0; y < tft.height(); y += 6)
    {
        tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    }
}

void testdrawtext(char *text, uint16_t color)
{
    tft.setCursor(0, 0);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2)
{
    tft.fillScreen(ST7735_BLACK);
    for (int16_t y = 0; y < tft.height(); y += 5)
    {
        tft.drawFastHLine(0, y, tft.width(), color1);
    }
    for (int16_t x = 0; x < tft.width(); x += 5)
    {
        tft.drawFastVLine(x, 0, tft.height(), color2);
    }
}

void testdrawrects(uint16_t color)
{
    tft.fillScreen(ST7735_BLACK);
    for (int16_t x = 0; x < tft.width(); x += 6)
    {
        tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
    }
}

void testfillrects(uint16_t color1, uint16_t color2)
{
    tft.fillScreen(ST7735_BLACK);
    for (int16_t x = tft.width() - 1; x > 6; x -= 6)
    {
        tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
        tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
    }
}

void testfillcircles(uint8_t radius, uint16_t color)
{
    for (int16_t x = radius; x < tft.width(); x += radius * 2)
    {
        for (int16_t y = radius; y < tft.height(); y += radius * 2)
        {
            tft.fillCircle(x, y, radius, color);
        }
    }
}

void testdrawcircles(uint8_t radius, uint16_t color)
{
    for (int16_t x = 0; x < tft.width() + radius; x += radius * 2)
    {
        for (int16_t y = 0; y < tft.height() + radius; y += radius * 2)
        {
            tft.drawCircle(x, y, radius, color);
        }
    }
}

void testtriangles()
{
    tft.fillScreen(ST7735_BLACK);
    int color = 0xF800;
    int t;
    int w = tft.width() / 2;
    int x = tft.height() - 1;
    int y = 0;
    int z = tft.width();
    for (t = 0; t <= 15; t++)
    {
        tft.drawTriangle(w, y, y, x, z, x, color);
        x -= 4;
        y += 4;
        z -= 4;
        color += 100;
    }
}

void tftPrintTest()
{
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 30);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(ST7735_YELLOW);
    tft.setTextSize(2);
    tft.println("Hello World!");
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(3);
    tft.println("Hello World!");
    tft.setTextColor(ST7735_BLUE);
    tft.setTextSize(4);
    tft.print(1234.567);
    delay(1500);
    tft.setCursor(0, 0);
    tft.fillScreen(ST7735_BLACK);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(0);
    tft.println("Hello World!");
    tft.println(" ");
    tft.print(8675309, HEX); // print 8,675,309 out in HEX!
    tft.println(" Print HEX!");
    tft.println(" ");
    tft.setTextColor(ST7735_WHITE);
    tft.println("Sketch has been");
    tft.println("running for: ");
    tft.setTextColor(ST7735_MAGENTA);
    tft.print(millis() / 1000);
    tft.setTextColor(ST7735_WHITE);
    tft.print(" seconds.");
}



































































