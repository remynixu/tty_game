#ifndef COLOR_H
#define COLOR_H

/* to minimize issues regarding colorings. */

#define INVALCLR	0xf

enum color_id{
	CID_BLACK = 0,
	CID_RED = 1,
	CID_GREEN = 2,
	CID_YELLOW = 3,
	CID_BLUE = 4,
	CID_PURPLE = 5,
	CID_CYAN = 6,
	CID_WHITE = 7
};

extern unsigned char mkclr(unsigned char fg, unsigned char bg);
extern int putclr(unsigned char clr);

#endif /* COLOR_H */
