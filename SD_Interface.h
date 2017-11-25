#ifndef _SD_INTERFACE_H
#define _SD_INTERFACE_H

#include <SPI.h>
#include <SD.h>

#define SD_CS 4

namespace SD_Interface
{

static bool initCard()
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

static bool loadLevel(int levelNum, byte out_level[], byte maxWaveCount)
{
    byte levels[2][4] = {
        {
            0xff,
            0x18,
            0x81,
            0x24,
        },
        {
            0xFF,
            0xE7,
            0xC5,
            0b01100110,
        }};
    Serial.println("Level loaded: ");
    for (int i = 0; i < maxWaveCount; i++)
    {
        out_level[i] = levels[levelNum - 1][i];
        Serial.println(out_level[i]);
    }
    return true;
}
}
#endif


