#ifndef _INPUTVALUES_H
#define _INPUTVALUES_H
// discrete inputs from thumbstick (TS)
enum INPUT_VALUES : byte
{
    TS_UP = 1,
    TS_DOWN = TS_UP << 1,
    TS_LEFT = TS_UP << 2,
    TS_RIGHT = TS_UP << 3,
    TS_FIRE = TS_UP << 4,
};

#endif
























































