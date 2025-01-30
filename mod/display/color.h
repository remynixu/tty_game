/*
 * color.h header file for general terminal coloring
 * for tty supporting basic ansi escape code colors.
 */

/*
 * It is best not to rely on module quirks.
 * Only do as intended, please.
 */


#ifndef COLOR_H
#define COLOR_H		1

#include <stdio.h>

/*
 * Attributes as required by ANSI Syntax.
 */
enum color_attr{
	CATTR_RESET = '0',
	CATTR_BOLD = '1',
	CATTR_UNDER = '4',
	CATTR_INVERSE = '7',
	CATTR_STRIKE = '9'
};

/*
 * Linux TTY Color IDs.
 */
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

#define COLOR_NULL	{CATTR_RESET, CID_WHITE, CID_BLACK}

/*
 * Pass to 'fput_color()' to clear screen.
 * Also the default.
 */
extern struct color *color_clear;

/*
 * Puts color to fstream.
 * Returns 0, or EOF.
 */
extern int fput_color(FILE *fstream, struct color *color);

/*
 * Clear up color!
 */
extern void color_cleanup(void);

/*
 * These are used to check for validity of a
 * color.
 * Returns 0(if invalid) or 1(if valid).
 */
extern int isvalcid(enum color_id cid);
extern int isvalcattr(enum color_attr cattr);
extern int isvalcolor(struct color *color);

#endif
