# Star Wurz
A simple shoot-them-up à la Space Invaders in C++.

This is an end of semester exam project in Autumn 2017 for the subject **PG5500 Embedded Systems** at Westerdals Oslo ACT. It demonstrates the use of a TFT LCD screen and SD card reader with the Arduino. The game is implemented as a finite state machine (Menu, Scoreboard, and Game). 

## Exam Presentation video
https://youtu.be/KmmKLQISIhg

## Current state
Most functions are placeholders, and the last version contains memory leaks. 
Only player movement has been implemented, no shooting yet.
As of the last version, the game requires the Arduino to be reset after ending the first game.

Needless to say, this is very much a work-in-progress.

## Requirements
- Must be run from the Arduino IDE (requires the **SPI.h** and **SD.h** libraries that come with it).

Libraries (can be downloaded from the Arduino IDE library manager):
- Adafruit_GFX 1.2.2
- Adafruit_ST7735 1.0.8

The content of the folder _SD card content_ should be placed **as-is** in the root folder of the SD card read by the game.