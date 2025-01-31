#ifndef COLOR_H
#define COLOR_H		1

#include <stdio.h>

#define COLOR_CLEAR	{CATTR_RESET, CID_WHITE, CID_BLACK}

enum color_attr{
	CATTR_RESET = '0',
	CATTR_BOLD = '1',
	CATTR_UNDER = '4',
	CATTR_INVERSE = '7',
	CATTR_STRIKE = '9'
};

enum color_id{
	CID_BLACK = '0',
	CID_RED,
	CID_GREEN,
	CID_YELLOW,
	CID_BLUE,
	CID_PURPLE,
	CID_CYAN,
	CID_WHITE
};

struct color{
	enum color_attr attr;
	enum color_id fg;
	enum color_id bg;
};

extern struct color color_clear;

extern int fput_color(FILE *fstream, struct color *color);
extern void color_cleanup(void);

extern int isvalcid(enum color_id cid);
extern int isvalcattr(enum color_attr cattr);
extern int isvalcolor(struct color *color);

#endif
