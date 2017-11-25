#ifndef _SD_INTERFACE_H
#define _SD_INTERFACE_H

#include <SPI.h>
#include <SD.h>

#define SD_CS 4

namespace SD_Interface
{
static byte level1[4] = {
    0x01,
    0x18,
    0x81,
    0b00100100
};
static byte level2[4] = {
    0xFF,
    0xE7,
    0xC5,
    0b01100110
};
static byte levels[][4] = {{level1}, {level2}};
static bool
initCard()
{
    return SD.begin(SD_CS);
}

static bool exists(String &filepath)
{
    return SD.exists(filepath);
}

static bool loadScores(int *out_scores, int &scorecount)
{
    const String scorefilepath = "scores.txt";
    File scores = SD.open(scorefilepath);
    if (scores)
    {
        int index = 0;
        String buffer = "";
        while (scores.available() && index < scorecount)
        {
            char c = scores.read();
            if (isDigit(c))
            {
                buffer += (char)c;
            }
            if (c == '\0' || c == '\n')
            {
                out_scores[index] = buffer.toInt();
                index++;
                buffer = "";
            }
        }
        // we flush the last one in case no '\n' was found before EOF
        if (buffer != "" && index < scorecount)
        {
            out_scores[index] = buffer.toInt();
            scorecount = index + 1;
        }

        scores.close();
        return true;
    }
    else
    {
        Serial.println("Could not find 'scores.txt'");
    }
    return false;
}

static bool loadLevel(int levelNum, byte *out_level, byte& maxWaveCount)
{
    maxWaveCount = 4;
    out_level = levels[levelNum - 1];
    return true;
}
}
#endif













