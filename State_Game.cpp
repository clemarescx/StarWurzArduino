#include "State_Game.h"
#include "State_Menu.h"
#include "State_Score.h"
#include "InputValues.h"
#include "GameWindow.h"
#include "SD_Interface.h"

#define centerToWingTipOffset 15

void State_Game::setGameVariables()
{
    numberOfLevels = SD_Interface::getLevelCount();
    SD_Interface::loadScores(highestScore, 1);
}

void State_Game::enter()
{
    Serial.println("Enter game.");
    setGameVariables();
    printGUI();
    loadLevel(levelIndex);
    resetLevel();
}

// game loop
IState *State_Game::execute(byte input)
{
    handleInputFlags(input);
    // update enemies position: move enemies down every gameSpeed tick
    if (millis() - timerStart >= 1000 / gameSpeed)
    {
        timerStart = millis();
        updateEnemyPositions();
        drawEnemies();
    }

    // check for collisions
    checkForCollisions();
    if (events & COLLISION_FLAG)
    {
        events &= (0xff ^ COLLISION_FLAG); // clear collision flag
        updateLives(-1);
        if (lives <= 0)
        {
            events |= LOSE_FLAG;
            return new State_Menu(tft);
        }
        else
        {
            resetLevel();
        }
    }
    // check for end of wave
    if (events & END_OF_WAVE_FLAG)
    {
        events &= (0xFF ^ END_OF_WAVE_FLAG); // clear the flag
        score++;
        waveIndex++;
        if (waveIndex == numberOfWaves)
        {
            levelIndex++;
            if (levelIndex >= numberOfLevels)
            {
                events |= WIN_FLAG;
                return new State_Menu(tft);
            }
            else
            {
                Serial.println("Load next level");
                loadLevel(levelIndex);
                resetLevel();
            }
        }
        else
        {
            Serial.println("Load next wave");
            loadWave(levelData[waveIndex]);
            clearGameScreen();
            drawPlayerShip(SHIP_COLOR);
        }
    }

    // draw ship
    if (input)
    {
        drawPlayerShip(SHIP_COLOR);
    }
    delay(10);
    return this;
}
void State_Game::exit()
{
    Serial.println("Exit game...");
    tft->fillScreen(ST7735_BLACK);
    tft->setCursor(10, 30);
    tft->setTextColor(ST7735_WHITE);
    tft->setTextSize(1);
    tft->print("Game Over!");
    tft->setCursor(10, 40);
    tft->setTextSize(2);
    if (events & WIN_FLAG)
    {
        tft->setTextColor(ST7735_GREEN);
        tft->print("YOU WIN!");
    }
    else
    {
        tft->setTextColor(ST7735_RED);
        tft->print("YOU LOSE!");
    }
    tft->setTextSize(1);
    tft->setTextColor(ST7735_YELLOW);
    tft->setCursor(30, 65);
    tft->print("Best score: ");
    tft->print(highestScore[0]);
    tft->setCursor(30, 75);
    tft->print("Your score: ");
    tft->print(score);
    delete[] enemies;
    delete[] levelData;
    delay(3000);
}

void State_Game::handleInputFlags(byte input)
{
    // update player position
    if (input & TS_FIRE)
    {
        // pending implementation :D
    }
    if (input & TS_LEFT)
    {
        movePlayerShipX(-5);
    }
    else if (input & TS_RIGHT)
    {
        movePlayerShipX(5);
    }
}

void State_Game::forAllEnemies(shipFunction f)
{
    for (int i = 0; i < enemyCount; i++)
    {
        (this->*f)(enemies[i]);
    }
}
void State_Game::checkForCollisions()
{
    forAllEnemies(&State_Game::flagCollisions);
}

void State_Game::flagCollisions(Ship &ship)
{
    if (collidesWithPlayer(ship))
    {
        events |= COLLISION_FLAG;
    }
    else if (collidesWithBottom(ship))
    {
        events |= END_OF_WAVE_FLAG;
    }
}

bool State_Game::collidesWithPlayer(const Ship &ship) const
{
    return ship.center.y + 6 >= playership.center.y - 10 &&
           ship.center.x + 4 >= playership.center.x - 5 &&
           ship.center.x - 4 <= playership.center.x + 5;
}

bool State_Game::collidesWithBottom(const Ship &ship) const
{
    return ship.center.y >= GameWindow::yMax;
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

void State_Game::updateLives(int update)
{
    Serial.println("One life lost");
    printLives(lives, ST7735_BLACK);
    lives += update;
    printLives(lives, ST7735_GREEN);
}

void State_Game::movePlayerShipX(const int offset)
{
    const byte clamped_x = playership.center.x + offset;
    if (GameWindow::x0 + centerToWingTipOffset < clamped_x &&
        clamped_x < GameWindow::xMax - centerToWingTipOffset - 1)
    {
        updatePlayerShipPos({clamped_x, playership.center.y});
    }
}

void State_Game::updatePlayerShipPos(const Point &pos)
{
    playership.old_pos = playership.center;
    playership.center = pos;
}

//// level management functions

void State_Game::loadLevel(const byte lvlIndex)
{
    delete[] levelData;
    levelData = new byte[numberOfWaves];
    SD_Interface::loadLevel(int(lvlIndex), levelData);
    // Serial.print("Load level ");
    // Serial.print(lvlIndex);
    Serial.println(" from State_Game: ");
    for (int i = 0; i < numberOfWaves; i++)
    {
        Serial.println(levelData[i]);
    }
    delay(100);
}

void State_Game::loadWave(byte wave)
{
    Serial.print("Load wave ");
    Serial.println(waveIndex);
    Serial.print("Wave loaded: ");
    Serial.println(wave);
    enemyCount = getEnemyCount(wave);
    delete[] enemies;
    enemies = new Ship[enemyCount];
    byte _wave = wave;
    byte bitIndex = 0;
    byte index = 0;
    delay(100);
    while (_wave)
    {
        if (_wave & 0x80)
        {
            byte x = GameWindow::spawnOffsetX * bitIndex + GameWindow::spawnOffsetX / 2;
            Point pos = {x, GameWindow::y0 + 5};
            enemies[index++] = {pos, pos};
        }
        bitIndex++;
        _wave <<= 1;
    }
    return enemies;
}

void State_Game::resetLevel()
{
    waveIndex = 0;
    loadWave(levelData[waveIndex]);
    resetPlayer();
}

void State_Game::resetPlayer()
{
    clearGameScreen();
    delay(100);

    playership.old_pos = GameWindow::playerStart;
    playership.center = GameWindow::playerStart;
    timerStart = millis();
    printShipInfo(playership);
    drawPlayerShip(SHIP_COLOR);
}

// one enemy per bit set in the wave byte
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

/// draw / print functions + helpers

void State_Game::printGUI()
{
    tft->setTextWrap(false);
    tft->fillScreen(ST7735_BLACK);
    tft->setCursor(0, 0);
    tft->setTextColor(ST7735_GREEN);
    tft->setTextSize(1);
    tft->print("Highest score: ");
    tft->println(highestScore[0]);
    tft->print("Lives: ");
    printLives(lives, ST7735_GREEN);
    tft->drawFastHLine(0, GameWindow::y0 - 1, GameWindow::xMax, ST7735_GREEN);
    delay(100);
}

void State_Game::printLevelBoard()
{
    clearGameScreen();
    tft->setCursor(10, 40);
    tft->setTextColor(ST7735_GREEN);
    tft->setTextSize(2);
    tft->print("LEVEL ");
    tft->print(levelIndex + 1);
    delay(100);
}

void State_Game::printLives(const byte _lives, uint16_t color) const
{
    tft->setCursor(38, 9);
    tft->setTextColor(color);
    tft->setTextSize(1);
    tft->print(_lives);
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
void State_Game::clearGameScreen() const
{
    tft->fillRect(GameWindow::x0, GameWindow::y0, GameWindow::xMax, GameWindow::xMax, ST7735_BLACK);
}






