#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "InputValues.h"

class InputManager
{
#define TS_X_PIN A0
#define TS_Y_PIN A1
#define TS_FIRE_PIN 2
    //Thumbstick pins
  public:
    InputManager()
    {
      // setup the thumbstick pins
      pinMode(TS_X_PIN, INPUT);
      pinMode(TS_Y_PIN, INPUT);
      pinMode(TS_FIRE_PIN, INPUT);
    }
    ~InputManager() {}

    byte pollForInput()
    {
      int ts_x, ts_y, ts_fire;
      ts_fire = digitalRead(TS_FIRE_PIN);
      ts_x = map(analogRead(TS_X_PIN), 0, 1010, -1, 1);
      ts_y = map(analogRead(TS_Y_PIN), 0, 1010, -1, 1);

      byte input = 0;
      // set FIRE bit
      if (ts_fire == 0)
      {
        input |= TS_FIRE; 
      }
      // set X direction bit
      switch (ts_x)
      {
        case 1:
          input |= TS_RIGHT;
          break;
        case -1:
          input |= TS_LEFT;
          break;
        default:
          break;
      }

      // set Y direction bit
      switch (ts_y)
      {
        case 1:
          input |= TS_DOWN;
          break;
        case -1:
          input |= TS_UP;
          break;
        default:
          break;
      }

      return input;
    }
};

#endif
































































