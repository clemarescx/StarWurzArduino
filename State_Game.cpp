#include "State_Game.h"
#include "State_Menu.h"
#include "State_Score.h"
#include "InputValues.h"
#include "GameWindow.h"
#include "SD_Interface.h"

#define centerToWingTipOffset 15

void State_Game::enter()
{
    int scoreCount = 1;
    SD_Interface::loadScores(&highestScore, scoreCount);
    printGUI();
    loadLevel(currentLevel);
    tft->fillRect(GameWindow::x0, GameWindow::y0, GameWindow::xMax, GameWindow::xMax, ST7735_BLACK);
    updateShipPos(GameWindow::playerStart);
    timerStart = millis();
}

// game loop
IState *State_Game::execute(byte input)
{
    // update player position
    if (input & TS_FIRE)
    {
        //return new State_Menu(tft);
    }
    if (input & TS_LEFT)
    {

        moveShipX(-5);
    }
    else if (input & TS_RIGHT)
    {
        moveShipX(5);
    }
    // update enemies position: move enemies down every gameSpeed tick
    if (millis()-timerStart >= gameSpeed){
        timerStart = millis();
        updateEnemyPositions();
    }

    // draw enemies

    // check for collisions
    // draw ship
    drawShip(SHIP_COLOR);

    return this;
}
void State_Game::exit()
{
    tft->fillScreen(ST7735_BLACK);
    tft->setCursor(10, 40);
    tft->setTextColor(ST7735_RED);
    tft->setTextSize(2);
    tft->print("Game Over!");
    tft->setTextSize(1);
    tft->setTextColor(ST7735_YELLOW);
    tft->setCursor(30, 65);
    tft->print("Best score: ");
    tft->print(highestScore);
    tft->setCursor(30, 75);
    tft->print("Your score: ");
    tft->print(currentScore);
    delay(3000);
}

void State_Game::updateEnemyPositions(){
    for (int i = 0; i < 8;  i++)
    {
        if(enemyPositions[i].y != 0)
            enemyPositions[i].y += 5;
    }
}

void State_Game::loadLevel(const byte lvl)
{
    delete[] levelData;
    delete[] enemyPositions;
    waveIndex = 0;
    SD_Interface::loadLevel(currentLevel, levelData, maxWaveCount);
    enemyPositions = parseWaveToEnemyStartingPos(levelData[waveIndex]);
}

Point *State_Game::parseWaveToEnemyStartingPos(byte wave)
{
    Point* enemies = new Point[8];
    byte _wave = wave;
    byte bitIndex = 0;
    while (_wave)
    {
        if (_wave & 0x80)
        {
            byte x = GameWindow::spawnOffsetX * bitIndex + (GameWindow::spawnOffsetX / 2);
            enemies[bitIndex] = {x, GameWindow::y0};
        }
        _wave <<= 1;
        bitIndex++;
    }
    return enemies;
}

void State_Game::printGUI()
{
    tft->setTextWrap(false);
    tft->fillScreen(ST7735_BLACK);
    tft->setCursor(0, 0);
    tft->setTextColor(ST7735_GREEN);
    tft->setTextSize(1);
    tft->print("Highest score: ");
    tft->println(highestScore);
    tft->print("Health: ");
    printHealth(currentHealth);
    tft->drawFastHLine(0, GameWindow::y0 - 1, GameWindow::xMax, ST7735_GREEN);
}

void State_Game::printHealth(const byte health) const
{
    tft->print(health);
}

void State_Game::moveShipX(const int offset)
{
    const byte clamped_x = playership.center.x + offset;
    if (GameWindow::x0 + centerToWingTipOffset < clamped_x &&
        clamped_x < GameWindow::xMax - centerToWingTipOffset - 1)
    {
        moveShip({clamped_x, playership.center.y});
    }
}

void State_Game::updateShipPos(const Point &pos)
{

    playership.center = pos;
    playership.body_nose = {pos.x, pos.y - 10};
    playership.body_back_left = {pos.x - 5, pos.y + 10};
    playership.body_back_right = {pos.x + 5, pos.y + 10};
    playership.wing_joint_left = {pos.x - 2, pos.y};
    playership.wing_joint_right = {pos.x + 2, pos.y};
    playership.wing_tip_left = {pos.x - centerToWingTipOffset, pos.y + 10};
    playership.wing_tip_right = {pos.x + centerToWingTipOffset, pos.y + 10};
    playership.gun_tip_left = {
        playership.wing_tip_left.x,
        playership.wing_tip_left.y - 5,
    };
    playership.gun_tip_right = {
        playership.wing_tip_right.x,
        playership.wing_tip_right.y - 5,
    };
}

void State_Game::drawTriangle(Point &p1, Point &p2, Point &p3, uint16_t color)
{
    tft->drawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
}

void State_Game::drawLine(Point &p1, Point &p2, uint16_t color)
{
    tft->drawLine(p1.x, p1.y, p2.x, p2.y, color);
}

void State_Game::drawFastHLine(Point &p, uint8_t len, uint16_t color)
{
    tft->drawFastHLine(p.x, p.y, len, color);
}

void State_Game::drawFastVLine(Point &p, uint8_t len, uint16_t color)
{
    tft->drawFastVLine(p.x, p.y, len, color);
}

void State_Game::drawShip(uint16_t color)
{
    //Body
    drawTriangle(playership.body_nose, playership.body_back_left, playership.body_back_right, color);
    //left side
    drawLine(playership.wing_joint_left, playership.wing_tip_left, color);
    drawFastHLine(playership.wing_tip_left, 10, color);
    drawFastVLine(playership.gun_tip_left, 5, color);

    // right side
    drawLine(playership.wing_joint_right, playership.wing_tip_right, color);
    drawFastHLine(playership.body_back_right, 10, color);
    drawFastVLine(playership.gun_tip_right, 5, color);
}

void State_Game::moveShip(const Point &newPos)
{
    drawShip(BG_COLOR);
    updateShipPos(newPos);
    drawShip(SHIP_COLOR);
}







