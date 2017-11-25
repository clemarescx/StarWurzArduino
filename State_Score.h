#ifndef _STATE_SCORE_H
#define _STATE_SCORE_H

#include "IState.h"

class State_Score : public IState{
  public:
    State_Score(Adafruit_ST7735 *tft) : IState(tft){    }
    void enter() override;
    IState *execute(byte input) override;
    void exit() override;
  private:
    void printScores(int *scores, int scoreCount);
    void sortScores(int *scores, int scoreCount);
};

#endif
































































