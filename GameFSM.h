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
    GameFSM(Adafruit_ST7735 *tft)
    {
        inputManager = InputManager();
        currentState = new State_Menu(tft);
    }
    void init()
    {
        currentState->enter();
    }
    void update()
    {
        byte input = inputManager.pollForInput();
        IState *newState = currentState->execute(input);
        if (newState != currentState)
        {
            input = 0;
            delay(200); // delay to let fire button go back to unpressed state 
            currentState->exit();
            delete currentState;
            newState->enter();
        }
        currentState = newState;
    }

  private:
    IState *currentState;
    InputManager inputManager;
};

#endif



















































