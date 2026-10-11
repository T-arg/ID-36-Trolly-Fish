#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(49, 20, T_arg, 0);
  if (globalCounter > 180)
  {
    globalCounter = 0;
    for (byte i = 0; i < 16; i++)
    {
      titleBubbles[i].resetPos(false);
    }
    gameState = STATE_MENU_MAIN;
  }
};

void stateMenuMain()
{
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, titleScreen, i);
  // PLAY on top, INFO and SFX below it
  sprites.drawPlusMask(86, 2, titleMenu_plus_mask, 0);
  sprites.drawPlusMask(73, 14, titleMenu_plus_mask, 1);
  sprites.drawPlusMask(99, 14, titleMenu_plus_mask, 2);
  sprites.drawPlusMask(menuY ? 73 + (menuX * 26) : 86, 2 + (menuY * 12), bubbles_plus_mask, bubblesFrame);
  if (arduboy.justPressed(RIGHT_BUTTON) && menuY && (!menuX)) menuX = !menuX;
  if (arduboy.justPressed(LEFT_BUTTON) && menuY && (menuX)) menuX = !menuX;
  if (arduboy.justPressed(DOWN_BUTTON) && (!menuY))
  {
    menuY = true;
    menuX = false;
  }
  if (arduboy.justPressed(UP_BUTTON) && (menuY)) menuY = false;
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = menuY ? STATE_MENU_INFO + menuX : STATE_MENU_PLAY;
}

void stateMenuHelp()
{
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuInfo()
{
  sprites.drawSelfMasked(14 , 8 , trollyFishTitle, 0);
  sprites.drawSelfMasked(26 , 30 , madeBy01, 0);
  sprites.drawSelfMasked(51 , 38 , madeBy02, 0);
  sprites.drawSelfMasked(30 , 50 , madeBy03, 0);
  drawWeed();
  drawBubbles(false);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, titleScreen, i);
  sprites.drawPlusMask(88  , 2 , soundMenu_plus_mask, 0);
  for (byte j = 0; j < 2; j++)
  {
    sprites.drawPlusMask(78 + (24 * j) , 14 , soundMenu_plus_mask, 1 + j);
  }
  sprites.drawPlusMask(76 + (arduboy.audio.enabled() * 22) , 14 , bubbles_plus_mask, bubblesFrame);
  if (arduboy.justPressed(RIGHT_BUTTON)) arduboy.audio.on();
  if (arduboy.justPressed(LEFT_BUTTON)) arduboy.audio.off();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
}


void stateMenuPlay()
{
  gameState = STATE_GAME_INIT_LEVEL;
}


#endif
