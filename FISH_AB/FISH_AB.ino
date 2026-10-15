/*
  Trolly Fish: https://t-arg.github.io/ID-36-Trolly-Fish/

  Arduboy version 2.0:  https://github.com/T-arg/ID-36-Trolly-Fish

  MADE by TEAM a.r.g. : https://t-arg.github.io/

  2016 - GAVENO - JO3RI - JUSTIN CRY

  2026 - MUSIC and SOUND EFFECTS - JO3RI

  License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 36

#include "globals.h"
#include "player.h"
#include "enemies.h"
#include "powerups.h"
#include "stage.h"
#include "inputs.h"
#include "menu.h"
#include "game.h"


typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateMenuJbox,
  stateGameInitLevel,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
};

void setup()
{
  arduboy.boot();
  arduboy.audio.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  if (arduboy.everyXFrames(6))bubblesFrame++;
  if (bubblesFrame > 12) bubblesFrame = 0;
  arduboy.clear();
  musicUpdate();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}
