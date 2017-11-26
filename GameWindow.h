#ifndef _GAMEWINDOW_H
#define _GAMEWINDOW_H
#include "Utils.h"

namespace GameWindow
{
static const byte x0 = 0;
const byte y0 = 160 - 128;
static const Point base_p = {0, y0};
static const byte xMax = 128;
static const byte yMax = 160;
static const Point max_p = {xMax, yMax};
static const Point center = {
    x0 + (max_p.x - x0) / 2,
    y0 + (max_p.y - y0) / 2,
};
static const Point playerStart = {
    x0 + (max_p.x - x0) / 2,
    yMax - 13,
};
static const byte enemyBBcenterOffset = 4; // +- offset for enemy to fit fine within spawn slot
static const byte spawnOffsetX = xMax / 8;
}

#endif




















































































































































































































