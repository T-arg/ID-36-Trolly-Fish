#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"

void stateMenuIntro()
{
  if (!arduboyIntro()) return;
  globalCounter++;
  sprites.drawSelfMasked(49, 20, T_arg, 0);
  drawTwinkles(49, 20, globalCounter);
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

// the main menu is a 2 x 2 grid:  PLAY JBOX / INFO CONF   (menuPos bit 0 = column, bit 1 = row)
const byte PROGMEM menuStates[] = { STATE_MENU_PLAY, STATE_MENU_JBOX, STATE_MENU_INFO, STATE_MENU_SOUNDFX };
const byte PROGMEM menuFrames[] = { 0, 3, 1, 2 };                 // PLAY JBOX INFO CONF in titleMenu_plus_mask

void stateMenuMain()
{
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, titleScreen, i);
  for (byte i = 0; i < 4; i++) sprites.drawPlusMask(73 + 26 * (i & 1), 2 + 12 * (i >> 1), titleMenu_plus_mask, pgm_read_byte(&menuFrames[i]));
  sprites.drawPlusMask(73 + 26 * (menuPos & 1), 2 + 12 * (menuPos >> 1), bubbles_plus_mask, bubblesFrame);
  byte old = menuPos;
  if (arduboy.justPressed(RIGHT_BUTTON)) menuPos |= 1;
  if (arduboy.justPressed(LEFT_BUTTON)) menuPos &= 2;
  if (arduboy.justPressed(DOWN_BUTTON)) menuPos |= 2;
  if (arduboy.justPressed(UP_BUTTON)) menuPos &= 1;
  if (menuPos != old) sfx(SFX_MOVE);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = pgm_read_byte(&menuStates[menuPos]);
    sfx(SFX_SELECT);
  }
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
  musicPickGameTune();                         // a different tune every game
  gameState = STATE_GAME_INIT_LEVEL;
}

// the jukebox: MUSIC (UP) and SNDFX (DOWN), LEFT = next number, RIGHT = previous number, B = play, A = stop (and leave when nothing plays)
byte jbRow = 0;
byte jbNr[2];                                  // MUSIC 0..6, SNDFX 0..9

// little arrows left and right of the number (2 x 3 pixels, frame 0 points left, frame 1 right)
const unsigned char PROGMEM jbArrow[] = { 2, 8, 0x02, 0x07, 0x07, 0x02 };

void stateMenuJbox()
{
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, titleScreen, i);
  for (byte i = 0; i < 2; i++)
  {
    byte y = 2 + 12 * i;
    sprites.drawSelfMasked(103, y + 3, jbArrow, 0);
    sprites.drawSelfMasked(120, y + 3, jbArrow, 1);
    sprites.drawPlusMask(76, y, jboxWords, 2 * i + (jbRow != i));              // the selected word is the lit one
    if (jbRow != i || (arduboy.frameCount & 16))                               // the selected number blinks
    {
      sprites.drawPlusMask(105, y, numbersSmall_plus_mask, (jbNr[i] + 1) / 10);
      sprites.drawPlusMask(112, y, numbersSmall_plus_mask, (jbNr[i] + 1) % 10);
    }
  }
  byte n = jbRow ? JBOX_SFX : JBOX_MUSIC;
  if (arduboy.justPressed(UP_BUTTON)) jbRow = 0;
  if (arduboy.justPressed(DOWN_BUTTON)) jbRow = 1;
  if (arduboy.justPressed(RIGHT_BUTTON)) jbNr[jbRow] = (jbNr[jbRow] + 1) % n;
  if (arduboy.justPressed(LEFT_BUTTON)) jbNr[jbRow] = (jbNr[jbRow] + n - 1) % n;
  if (arduboy.justPressed(B_BUTTON) && arduboy.audio.enabled())
  {
    if (jbRow) sfx(jbNr[1]);
    else musicPlay(jbNr[0]);
  }
  if (arduboy.justPressed(A_BUTTON))
  {
    if (musicId == MUSIC_OFF) gameState = STATE_MENU_MAIN;    // nothing playing: leave, the title tune restarts
    else musicPlay(MUSIC_OFF);
  }
}


#endif
