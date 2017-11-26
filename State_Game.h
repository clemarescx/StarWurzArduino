#ifndef _STATE_GAME_H
#define _STATE_GAME_H

#include "IState.h"

#define SHIP_COLOR ST7735_MAGENTA
#define BG_COLOR ST7735_BLACK

class State_Game : public IState
{

public:
  State_Game(Adafruit_ST7735 *tft) : IState(tft)
  {
  }
  ~State_Game()
  {
  }
  void enter() override;
  IState *execute(byte input) override;
  void exit() override;

private:
  enum EVENT_FLAGS
  {
    COLLISION_FLAG = 1,
    END_OF_WAVE_FLAG = 2,
    WIN_FLAG = 8,
    LOSE_FLAG = 16,
  };

  unsigned long timerStart = 0;
  int highestScore[1];
  int score = 0;
  byte lives = 3;
  byte levelIndex = 0;
  byte numberOfLevels = 0;
  byte numberOfWaves = 4;
  byte enemyCount = 0;
  int gameSpeed = 10;

  byte waveIndex = 0;
  byte *levelData;

  struct Ship
  {
    Point center;
    Point old_pos;
  };

  Ship playership;
  Ship *enemies;
  byte events = 0;

  //// game logic functions
  typedef void (State_Game::*shipFunction)(Ship &);
  void forAllEnemies(shipFunction f);
  void movePlayerShipX(int offset);
  void updatePlayerShipPos(const Point &pos);
  void drawEnemies();
  void updateEnemyPositions();
  void updatePosition(Ship &ship);
  void handleInputFlags(byte input);
  void checkForCollisions();
  void updateLives(int update);
  void flagCollisions(Ship &ship);
  bool collidesWithPlayer(const Ship &ship) const;
  bool collidesWithBottom(const Ship &ship) const;

  //// level data functions
  void setGameVariables();
  void resetLevel();
  void loadLevel(const byte lvl);
  void resetPlayer();
  byte getEnemyCount(byte wave);
  void loadWave(byte wave);

  //// helper draw functions
  void drawTriangle(const Point &p1, const Point &p2, const Point &p3, uint16_t color);
  void drawLine(const Point &p1, const Point &p2, uint16_t color);
  void drawFastHLine(const Point &p, uint8_t len, uint16_t color);
  void drawFastVLine(const Point &p, uint8_t len, uint16_t color);
  void drawPlayerShip(uint16_t color);
  void drawPlayerShip(const Point &pos, uint16_t color);
  void drawEnemy(const Point &pos, uint16_t color);
  void clearAndDrawEnemy(Ship &ship);
  void clearGameScreen() const;
  void printLives(const byte lives, uint16_t color) const;
  void printGUI();
  void printLevelBoard();

  /// debug
  void printShipInfo(const Ship &ship) const
  {
    String coords = String("[");
    String x = String(ship.center.x);
    String y = String(ship.center.y);
    coords += x + "," + y + "]";
    Serial.println(coords);
  }
};

#endif























