#ifndef _STATE_GAME_H
#define _STATE_GAME_H

#include "IState.h"

#define SHIP_COLOR ST7735_MAGENTA
#define BG_COLOR ST7735_BLACK

class State_Game : public IState
{
  public:
    State_Game(Adafruit_ST7735 *tft) : IState(tft) {}
    ~State_Game() {}
    void enter()override;
    IState *execute(byte input)override;
    void exit()override;

  private:
    unsigned long timerStart;
    int highestScore = 0;
    int currentScore = 0;
    byte currentHealth = 3;
    byte currentLevel = 1;
    int gameSpeed = 1000; //enemies move every 10 frame
    
    byte waveIndex = 0;
    byte maxWaveCount;
    byte *levelData;

    Point* enemyPositions;
    struct
    {
        Point center;
        Point body_nose;
        Point body_back_left;
        Point body_back_right;
        Point wing_joint_left;
        Point wing_joint_right;
        Point wing_tip_left;
        Point wing_tip_right;
        Point gun_tip_left;
        Point gun_tip_right;
    } playership;

    struct EnemyShip{
      Point center;
      Point body_back_left;
      Point body_back_right;
      Point body_nose;
      Point gun_tip_left;
      Point gun_tip_right;
    } enemy;

    void updateEnemyPositions();
    void loadLevel(const byte lvl);
    Point* parseWaveToEnemyStartingPos(byte wave);
    void printHealth(const byte health) const;
    void printGUI();

    void moveShipX(int offset);

    void updateShipPos(const Point &pos);
    void drawTriangle(Point &p1, Point &p2, Point &p3, uint16_t color);

    void drawLine(Point &p1, Point &p2, uint16_t color);
    void drawFastHLine(Point &p, uint8_t len, uint16_t color);

    void drawFastVLine(Point &p, uint8_t len, uint16_t color);
    void drawShip(uint16_t color);

    void moveShip(const Point &newPos);
};

#endif







