#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include "ATMconfig.h"
#include <ATMlib.h>
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1
#define STATE_MENU_HELP              2
#define STATE_MENU_PLAY              3
#define STATE_MENU_INFO              4
#define STATE_MENU_SOUNDFX           5
#define STATE_MENU_JBOX              6

//define game states (on main menu)
#define STATE_GAME_INIT_LEVEL        7
#define STATE_GAME_PLAYING           8
#define STATE_GAME_PAUSE             9
#define STATE_GAME_OVER              10


Arduboy2Base arduboy;
Sprites sprites;
ATMsynth ATM;

//determines the state of the game
byte gameState = STATE_MENU_INTRO;   // start the game with the TEAM a.r.g. logo
byte globalCounter = 0;

// These are all getting a value in STATE_GAME_INIT
unsigned long scorePlayer;
byte counter = 0;
byte pu_current = 0;
byte bubblesFrame = 0;
byte menuPos = 0;            // main menu: bit 0 = right column, bit 1 = bottom row (PLAY JBOX / INFO CONF)

#define INTRO_DIV 2
#include "arduboy_intro.h"
#include "music.h"

#endif
