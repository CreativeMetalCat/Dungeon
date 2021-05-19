#pragma once

#define PDCURSES

#ifdef PDCURSES
#include "pdcurses/include/curses.h"

#define ADD_CHAR_AT mvaddch 
#define ADD_CHAR addch
#define PRINT_AT_W mvprintw
#endif