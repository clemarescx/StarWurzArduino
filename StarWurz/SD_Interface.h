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
/*
static byte parseToByte(String& str) {
  byte res = 0;
  for (int i = 0; i < 8; i++)
  {
    if (str.charAt(i) == '1') {
      res |= 0x01;
    }
    if (i < 7)
    {
      res <<= 1;
    }
  }
  return res;
}
*/
static bool loadLevel(int levelIndex, byte out_level[])
{
  /*if (SD.exists("levels/")) {
    Serial.println("found levels/");
  } else {
    Serial.println("levels/ not found");
  }

  String filepath = String("levels/");
  filepath.concat(levelIndex + 1);
  filepath.concat(".txt");
  //   Serial.print("opening ");
  //   Serial.println(filepath.c_str());
  File level = SD.open(filepath.c_str());
  String buffer = "";
  if (level)
  {
    Serial.println("Level opened.");
    int index = 0;
    while (level.available())
    {
      byte c = level.read();
      if (isDigit(c))
      {
        buffer += (char)c;
      }

      if (c == '\0' || c == '\n')
      {
        byte lvl = parseToByte(buffer);
        out_level[index] = lvl;
        Serial.println(out_level[index]);
        index++;
        buffer = "";
      }
    }
  level.close();
  return true;
  }
  else*/
  {
    Serial.print("Could not load from card.");
    byte levels[2][4] = {
      {
        0b11110000, //240
        0b00011000, //24
        0b10000001, //129
        0b11000011, //195
      },
      {
        0b11000000, //192
        0b01100000, //96
        0b00110000, //48
        0b00011000, //24
      }
    };
    for (int i = 0; i < 4; i++)
    {
      out_level[i] = levels[levelIndex][i];
      Serial.println(out_level[i]);
    }
  }

  return true;
}
}
#endif













































