#include "State_Game.h"
#include "State_Menu.h"
#include "State_Score.h"
#include "InputValues.h"
#include "GameWindow.h"
#include "SD_Interface.h"

#define centerToWingTipOffset 15
#define WAVECOUNT_PER_LVL 4

void State_Game::enter()
{
    int scoreCount = 1;
    SD_Interface::loadScores(&highestScore, scoreCount);
    printGUI();
    loadLevel(currentLevel);
    tft->fillRect(GameWindow::x0, GameWindow::y0, GameWindow::xMax, GameWindow::xMax, ST7735_BLACK);
    updateShipPos(GameWindow::playerStart);
    timerStart = millis();
    drawPlayerShip(playership.center, SHIP_COLOR);
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
    if (millis() - timerStart >= 1000 / gameSpeed)
    {
        timerStart = millis();
        updateEnemyPositions();
        drawEnemies();
    }
    // draw enemies

    // check for collisions
    // draw ship
    if (input)
    {
        drawPlayerShip(SHIP_COLOR);
    }
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

void State_Game::forAllEnemies(shipFunction f)
{
    for (int i = 0; i < currentWaveEnemyCount; i++)
    {
        (this->*f)(enemies[i]);
    }
}

void State_Game::updateEnemyPositions()
{
    forAllEnemies(&State_Game::updatePosition);
}
void State_Game::updatePosition(Ship &ship)
{
    ship.old_pos = ship.center;
    ship.center.y += 5;
}
void State_Game::drawEnemies()
{
    forAllEnemies(&State_Game::clearAndDrawEnemy);
}

void State_Game::clearAndDrawEnemy(Ship &ship)
{
    drawEnemy(ship.old_pos, ST7735_BLACK);
    drawEnemy(ship.center, ST7735_RED);
}
void State_Game::drawEnemy(const Point &pos, uint16_t color)
{
    Point nose = {pos.x, pos.y + 6};
    Point back_left = {pos.x - 4, pos.y - 6};
    Point back_right = {pos.x + 4, pos.y - 6};
    drawTriangle(nose, back_left, back_right, color);
    drawFastVLine(back_left, 6, color);
    drawFastVLine(back_right, 6, color);
}

void State_Game::loadLevel(const byte lvl)
{
    delete[] levelData;
    levelData = new byte[WAVECOUNT_PER_LVL];
    waveIndex = 0;
    SD_Interface::loadLevel(currentLevel, levelData, WAVECOUNT_PER_LVL);
    Serial.println("Level from State_Game: ");
    Serial.println(levelData[0]);
    Serial.println(levelData[1]);
    Serial.println(levelData[2]);
    Serial.println(levelData[3]);
    loadWave(levelData[waveIndex]);
}

void State_Game::loadWave(byte wave)
{
    Serial.print("Wave loaded : ");
    Serial.println(wave);
    currentWaveEnemyCount = getEnemyCount(wave);
    delete[] enemies;
    enemies = new Ship[currentWaveEnemyCount];
    byte _wave = wave;
    byte bitIndex = 0;
    byte index = 0;
    while (_wave)
    {
        if (_wave & 0x80)
        {
            byte x = GameWindow::spawnOffsetX * bitIndex + GameWindow::enemyBBcenterOffset;
            Point pos = {x, GameWindow::y0 + 3};
            enemies[index++] = {pos, pos};
        }
        bitIndex++;
        _wave <<= 1;
    }
    return enemies;
}

byte State_Game::getEnemyCount(byte wave)
{
    byte count = 0;
    if (wave == 0)
        return count;
    byte _wave = wave;
    do
    {
        count += (_wave & 0x01);
    } while (_wave >>= 1);
    return count;
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
        updateShipPos({clamped_x, playership.center.y});
    }
}

void State_Game::updateShipPos(const Point &pos)
{
    playership.old_pos = playership.center;
    playership.center = pos;
}

void State_Game::drawPlayerShip(uint16_t color)
{
    drawPlayerShip(playership.old_pos, ST7735_BLACK);
    drawPlayerShip(playership.center, color);
}

void State_Game::drawPlayerShip(const Point &pos, uint16_t color)
{
    const Point body_nose = {pos.x, pos.y - 10};
    const Point body_back_left = {pos.x - 5, pos.y + 10};
    const Point body_back_right = {pos.x + 5, pos.y + 10};
    const Point wing_joint_left = {pos.x - 2, pos.y};
    const Point wing_joint_right = {pos.x + 2, pos.y};
    const Point wing_tip_left = {pos.x - centerToWingTipOffset, pos.y + 10};
    const Point wing_tip_right = {pos.x + centerToWingTipOffset, pos.y + 10};
    const Point gun_tip_left = {
        pos.x - centerToWingTipOffset,
        pos.y + 5,
    };
    const Point gun_tip_right = {
        pos.x + centerToWingTipOffset,
        pos.y + 5,
    };

    //Body
    drawTriangle(body_nose, body_back_left, body_back_right, color);
    //left side
    drawLine(wing_joint_left, wing_tip_left, color);
    drawFastHLine(wing_tip_left, 10, color);
    drawFastVLine(gun_tip_left, 5, color);

    // right side
    drawLine(wing_joint_right, wing_tip_right, color);
    drawFastHLine(body_back_right, 10, color);
    drawFastVLine(gun_tip_right, 5, color);
}

void State_Game::drawTriangle(const Point &p1, const Point &p2, const Point &p3, uint16_t color)
{
    tft->drawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
}

void State_Game::drawLine(const Point &p1, const Point &p2, uint16_t color)
{
    tft->drawLine(p1.x, p1.y, p2.x, p2.y, color);
}

void State_Game::drawFastHLine(const Point &p, uint8_t len, uint16_t color)
{
    tft->drawFastHLine(p.x, p.y, len, color);
}

void State_Game::drawFastVLine(const Point &p, uint8_t len, uint16_t color)
{
    tft->drawFastVLine(p.x, p.y, len, color);
}
