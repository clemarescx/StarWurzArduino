#ifndef _GAMEFSM_H
#define _GAMEFSM_H
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "IState.h"
#include "InputManager.h"

#include "State_Menu.h"

class GameFSM
{
  public:
    GameFSM(Adafruit_ST7735 *tft);
    ~GameFSM();

    void init();
    void update();

  private:
    IState *currentState;
    InputManager inputManager;
};

#endif



















































