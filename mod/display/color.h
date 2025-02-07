#ifndef COLOR_H
#define COLOR_H		1

#ifndef __no_ansi

#include "./color/ansi.h"

/* the options available for coloring the
 * screen are here. */

enum color_id{
	CID_BLACK = AC_BLACK,
	CID_RED = AC_RED,
	CID_GREEN = AC_GREEN,
	CID_YELLOW = AC_YELLOW,
	CID_BLUE = AC_BLUE,
	CID_PURPLE = AC_PURPLE,
	CID_CYAN = AC_CYAN,
	CID_WHITE = AC_WHITE
};

/* make a valid color info, returns it as a byte.
 * returns 0 if invalid arguments. */

#define mkclr(fg, bg)	mkansiclr((fg), (bg))

/* checks if the id is a valid color id for the
 * current implementation. non-zero = yes, 0 = no. */

#define isvalcid(id)	isvalansicid((id))

/* checks if the byte is a valid color info for the
 * current implementation. non-zero = yes, 0 = no. */

#define isvalclr(byte)	isvalansiclr((byte))

/* changes the color of the next print,
 * returns non-zero on success, IO_ERR on fail. */

#define putclr(clr)	putansiclr((clr))

#else

/* you are required to fill these out if you'll
 * use a different library and follow the expected
 * behaviors above.
 *
 * also, please put the implementations to abstract, on
 * the ./color directory. thank you. */

#include	"./color/*"

enum color_attr{
};

enum color_id{
};

#define mkclr(fg, bg)
#define isvalcid(id)
#define isvalclr(byte)
#define putclr(clr)

#endif /* !__no_ansi */

#endif /* COLOR_H */
