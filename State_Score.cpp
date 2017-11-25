#include "State_Score.h"
#include "State_Menu.h"
#include "InputValues.h"
#include "SD_Interface.h"

void State_Score::enter()
{
    int scores[5] = {0,0,0,0,0};
    int scoreCount = 5;
    if (SD_Interface::loadScores(scores, scoreCount))
    {
        sortScores(scores, scoreCount);
        printScores(scores, scoreCount);
    }
    // load from SD card
}

IState *State_Score::execute(byte input)
{
    if (input & TS_FIRE)
    {
        return new State_Menu(tft);
    }
}
void State_Score::exit()
{
}
void State_Score::printScores(int *scores, int count)
{
    int _count = constrain(count, 0, 10);
    tft->setCursor(5, 20);
    tft->setTextColor(ST7735_YELLOW);
    tft->setTextSize(2);
    tft->print("HIGHSCORES");
    tft->setTextSize(1);
    tft->setTextColor(ST7735_WHITE);
    for (int i = 0; i < _count; i++)
    {
        tft->setCursor(35, 50 + (i * 10));
        tft->print(i + 1);
        tft->print(". ");
        tft->print(scores[i]);
    }
}

void swap(int *lhs, int *rhs)
{
    int temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

void State_Score::sortScores(int *scores, int count)
{
    if (count <= 1)
    {
        Serial.println("Not enough scores to sort");
        return;
    }
    bool swapped;
    for (int i = 0; i < count-1; i++)
    {
        swapped = false;
        for (int j = 0; j < count - i; j++)
        {
            if (scores[j] < scores[j + 1])
            {
                swapped = true;
                int tmp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tmp;
            }
        }
        if (!swapped)
            break;
    }
}








































































































