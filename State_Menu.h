#ifndef _STATE_MENU_H
#define _STATE_MENU_H

#include "IState.h"


class State_Menu : public IState
{
  public:
    State_Menu(Adafruit_ST7735 *tft) : IState(tft) {}
    ~State_Menu() {}
    void enter() override;
    IState *execute(byte input) override;
    void exit() override;

  private:
    byte selectedItem;

    #define caretBaseX 40
    #define caretBaseY 62
    #define caretOffset 10
    
    byte caretPosY = caretBaseY;
    void selectItem(byte itemIndex);

    void printTitleScreen();
};

#endif





























































