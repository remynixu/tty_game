#ifndef SCR_H
#define SCR_H

#include <stdint.h>
#include <stddef.h>

/*
 * Color refers to ANSI color code.
 */

enum color_code{
	COLOR_BLACK = 0,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_CYAN,
	COLOR_WHITE
};

uint8_t mkcolor(int attr, uint8_t fg, uint8_t bg);

enum frcolor_how{
	COLOR_ATTR,
	COLOR_FG,
	COLOR_BG
};

uint8_t frcolor(uint8_t color, int how);

int put_ansi_color(uint8_t code);
int putcolor(uint8_t color);

/*
 * An entry (etr) is an ASCII character with info made for ANSI color coding.
 */

uint16_t mketr(int attr, uint8_t fg, uint8_t bg, char c);

enum fretr_how{
	ETR_COLOR,
	ETR_CHAR
};

uint8_t fretr(uint16_t etr, int how);

int putetr(uint16_t etr);
int printetr(uint16_t *etr, size_t sz);

/*
 * A screen (scr) is a buffer of entries on the terminal used for simpler
 * control.
 */

#define SCRWIDTH	30
#define SCRHEIGHT	15
#define SCRSIZE	(SCRWIDTH * SCRHEIGHT)

void fillscr(uint16_t etr);
void clearscr(void);

void scrput(uint16_t etr, uint8_t x, uint8_t y);
uint16_t scrget(uint8_t x, uint8_t y);

int nextline(void);
int putscr(void);

#endif
