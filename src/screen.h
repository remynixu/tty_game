#ifndef SCREEN_H
#define SCREEN_H

#include <stddef.h>


extern struct screen_error{
	enum{
		SUCCESS,
		IO_ERROR,
		BAD_SYMBOL
	}code;
	char *str;
}screen_error;

enum icon_color{
	ICON_BLACK = 0,
	ICON_RED,
	ICON_GREEN,
	ICON_YELLOW,
	ICON_BLUE,
	ICON_PURPLE,
	ICON_CYAN,
	ICON_WHITE
};

struct icon{
	unsigned int glow : 1;
	unsigned int symbol : 7;
	unsigned int fg : 4;
	unsigned int bg : 4;
};

#define mkicon(g, s, f, b)	\
	(struct icon){g, s, f, b}

#define SCREEN_HEIGHT	15
#define SCREEN_WIDTH	(2 * SCREEN_HEIGHT)
#define SCREEN_SIZE	(SCREEN_WIDTH *	\
		SCREEN_HEIGHT)

void fillscr(struct icon ic);
void clearscr(void);
void scrput(struct icon ic, size_t x,
		size_t y);
struct icon scrget(size_t x, size_t y);

int putscr(void);

#endif
