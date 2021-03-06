#include "State_Menu.h"
#include "State_Game.h"
#include "State_Score.h"
#include "InputValues.h"

void State_Menu::enter()
{
    tft->fillScreen(ST7735_BLACK);
    // print options and select 1st
    printTitleScreen();
    selectItem(0);
}

IState *State_Menu::execute(byte input)
{

    // change selection caret according to input
    if (input & TS_UP)
    {
        if (selectedItem != 0)
            selectItem(0);
    }
    else if (input & TS_DOWN)
    {
        if (selectedItem != 1)
            selectItem(1);
    }

    // switch to selected item with fire
    if (input & TS_FIRE)
    {
        switch (selectedItem)
        {
        case 0:
            return new State_Game(tft);
        case 1:
            return new State_Score(tft);
        }
    }
    return this;
}

void State_Menu::exit()
{
}

void State_Menu::selectItem(byte itemIndex)
{
    selectedItem = itemIndex;
    tft->setCursor(caretBaseX, caretPosY);
    tft->setTextColor(ST7735_BLACK);
    tft->print('>');
    caretPosY = caretBaseY + caretOffset * itemIndex;
    tft->setCursor(caretBaseX, caretPosY);
    tft->setTextColor(ST7735_WHITE);
    tft->print('>');
}

void State_Menu::printTitleScreen()
{
    tft->setCursor(10, 30);
    tft->setTextColor(ST7735_GREEN);
    tft->setTextSize(2);
    tft->print("STAR WURZ");
    tft->setTextSize(1);
    tft->setTextColor(ST7735_WHITE);
    tft->setCursor(50, 60);
    tft->println("start");
    tft->setCursor(50, 70);
    tft->println("scores");
}




























