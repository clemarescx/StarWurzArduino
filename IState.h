#ifndef _ISTATE_H
#define _ISTATE_H

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#include "Utils.h"

using namespace Utils;

class IState
{
  public:
    IState(Adafruit_ST7735 *_tft) : tft(_tft){}
    virtual ~IState() {}
    virtual void enter() = 0;
    virtual IState *execute(byte input) = 0;
    virtual void exit() = 0;
  protected:
    Adafruit_ST7735 *tft;
};
#endif












































































































































