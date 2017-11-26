#include "GameFSM.h"

GameFSM::GameFSM(Adafruit_ST7735 *tft)
{
    inputManager = InputManager();
    currentState = new State_Menu(tft);
}
GameFSM::~GameFSM()
{
    delete currentState;
}
void GameFSM::init()
{
    currentState->enter();
}
void GameFSM::update()
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
































































