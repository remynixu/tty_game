#ifndef COLOR_H
#define COLOR_H		1

#include <stdio.h>

enum color_id{
	CID_BLACK = 0x0,
	CID_RED = 0x1,
	CID_GREEN = 0x2,
	CID_YELLOW = 0x3,
	CID_BLUE = 0x4,
	CID_PURPLE = 0x5,
	CID_CYAN = 0x6,
	CID_WHITE = 0x7
};

enum color_attr{
	CATTR_CLEAR = 0x0,
	CATTR_BOLD = 0x1
};

extern unsigned char getbytebitn(unsigned char byte, unsigned char nmemb, unsigned char offset);
extern unsigned char mkclr(enum color_attr attr, enum color_id fg, enum color_id bg);

extern int isvalclr(unsigned char clr);
extern int fputclr(FILE *f, unsigned char clr);

#endif /* COLOR_H */
