#include "State_Score.h"
#include "State_Menu.h"
#include "InputValues.h"
#include "SD_Interface.h"

void State_Score::enter()
{    
    tft->fillScreen(ST7735_BLACK);
    byte scoreCount = 4;
    int scores[4];
    if (SD_Interface::loadScores(scores, scoreCount))
    {
        printScores(scores, scoreCount);
    }
}

IState *State_Score::execute(byte input)
{
    if (input & TS_FIRE)
    {
        return new State_Menu(tft);
    }
}
void State_Score::exit(){    
}

void State_Score::printScores(int *scores, int count)
{
    tft->setCursor(5, 20);
    tft->setTextColor(ST7735_YELLOW);
    tft->setTextSize(2);
    tft->print("HIGHSCORES");
    tft->setTextSize(1);
    tft->setTextColor(ST7735_WHITE);
    for (int i = 0; i < count; i++)
    {
        tft->setCursor(35, 50 + (i * 10));
        tft->print(i + 1);
        tft->print(". ");
        tft->print(scores[i]);
    }
}




























