#ifndef _SD_INTERFACE_H
#define _SD_INTERFACE_H

#include <SPI.h>
#include <SD.h>


namespace SD_Interface
{



static bool loadScores(int *out_scores, byte scorecount)
{
    File scores = SD.open("scores.txt");
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

static byte getLevelCount()
{
    byte levelCount = 0;
    File levelDir = SD.open("levels/");
    if (levelDir)
    {
        while (true)
        {
            File f = levelDir.openNextFile();
            if (!f)
                break;
            levelCount++;
        }
    }
    else
    {
        Serial.println("Could not open 'levels/'");
    }
    Serial.print("Found ");
    Serial.print(int(levelCount));
    Serial.println(" levels");
    levelDir.close();
    return levelCount;
}

static byte parseToByte(String& str){
    byte res = 0;
    for (int i=0; i <8; i++)
    {
        if(str.charAt(i)=='1')
        {res |=0x01;
                }
        res <<= 1;
        }
        return res;
}

static bool loadLevel(int levelIndex, byte out_level[])
{
    if(SD.exists("levels/")){
        Serial.println("found levels/");
    } else{
        Serial.println("levels/ not found");        
    }
    String filepath = String("/levels/");
    filepath.concat(levelIndex + 1);
    filepath.concat(".txt");
    File level = SD.open(filepath.c_str());
    String buffer = "";
    if (level)
    {
        int index = 0;            
        while (level.available())
        {
            char c = level.read();
            if(isDigit(c))
            buffer += (char)c;

            if (c == '\0' || c == '\n')
            {
                byte lvl = parseToByte(buffer);
                out_level[index] = lvl;
                index++;
                buffer = "";
            }
        }
        //buffer.getBytes(out_level, buffer.length());
    }
    else
    {
        Serial.print("Could not load ");
        Serial.println(filepath.c_str());
    }
    level.close();
    // byte levels[2][4] = {
    //     {
    //         0b11110000,
    //         0b00011000,
    //         0b10000001,
    //         0b11000011,
    //     },
    //     {
    //         0b11000000,
    //         0b01100000,
    //         0b00110000,
    //         0b00011000,
    //     }};

    Serial.println("Level loaded: ");
    for (int i = 0; i < buffer.length(); i++)
    {
        
        Serial.println(out_level[i]);
    }
    return true;
}
}
#endif
























