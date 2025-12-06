#ifndef SCREEN_H
#define SCREEN_H

/*
 * Alright, the game needs a screen to work, so here we go...
 *
 * This works in C90 btw, and only works on the terminal. It also needs the
 * terminal to be as wide and tall as SCREEN_WIDTH and SCREEN_HEIGHT defines
 * respectively!
 *
 * - remynixu
 */

/* Constants here! */
#include "framework/presets.h"

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH	16
#endif /* SCREEN_WIDTH */

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT	32
#endif /* SCREEN_HEIGHT */

#ifndef UNICODE_SUPPORT
#define UNICODE_SUPPORT	0
#endif /* UNICODE_SUPPORT */



/* Functions */



#endif /* SCREEN_H */
