#ifndef _STATE_GAME_H
#define _STATE_GAME_H

#include "IState.h"

#define SHIP_COLOR ST7735_MAGENTA
#define BG_COLOR ST7735_BLACK

class State_Game : public IState
{
public:
  State_Game(Adafruit_ST7735 *tft) : IState(tft) {}
  ~State_Game()
  {
    delete[] enemies;
    delete[] levelData;
  }
  void enter() override;
  IState *execute(byte input) override;
  void exit() override;

private:
  unsigned long timerStart;
  int highestScore = 0;
  int currentScore = 0;
  byte currentHealth = 3;
  byte currentLevel = 1;
  byte currentWaveEnemyCount = 0;
  int gameSpeed = 2; //enemies move every 10 frame

  byte waveIndex = 0;
  byte *levelData;

  struct Ship
  {
    Point center;
    Point old_pos;
  };

  Ship playership;
  Ship *enemies;

  void loadLevel(const byte lvl);
  byte getEnemyCount(byte wave);
  void loadWave(byte wave);
  void printHealth(const byte health) const;
  void printGUI();

  void moveShipX(int offset);

  void updateShipPos(const Point &pos);
  void drawTriangle(const Point &p1, const Point &p2, const Point &p3, uint16_t color);

  void drawLine(const Point &p1, const Point &p2, uint16_t color);
  void drawFastHLine(const Point &p, uint8_t len, uint16_t color);

  void drawFastVLine(const Point &p, uint8_t len, uint16_t color);
  void drawPlayerShip(uint16_t color);
  void drawPlayerShip(const Point &pos, uint16_t color);
  typedef void (State_Game::*shipFunction)(Ship &);
  void forAllEnemies(shipFunction f);
  void drawEnemies();
  void drawEnemy(const Point &pos, uint16_t color);
  void clearAndDrawEnemy(Ship &ship);
  void updateEnemyPositions();
  void updatePosition(Ship &ship);
};

#endif





