#include "screen.h"

/*
 * IMPLEMENTATION
 *
 * A screen is an array of colored characters that is displayed in terminal or
 * similar environments.
 *
 * It has an array of:
 * - Color     - Info about the color of the "Character", made of:
 *             - Foreground - The main color of the Character.
 *             - Background - The surrounding color of the Character.
 * - Character - An ASCII character, can be unicode if you're quirky :>
 *               This is why the user can define if the screen must be "wide" or
 *               "slim" for screen flexibility, see "Screen type" for more.
 *             - Note: Not all devices supports "wchar_t" therefore it must be
 *               possible to disable through the macro "UNICODE_SUPPORT".
 *
 * The dimensions of the array is defined by:
 * - Screen type   - Defines if the screen uses unicode or ascii characters.
 *                   Unlike others, it is not a constant and can be defined by
 *                   the user. Here are the values:
 *                 - Wide - If the screen uses unicode characters.
 *                 - Slim - If the screen uses ascii characters only.
 * - SCREEN_WIDTH  - The size of the row to display in the terminal.
 * - SCREEN_HEIGHT - The size of the column to display in the terminal.
 */

/*
 * Abbreviated terms:
 * scr	| screen
 * pos	| position
 * str	| string
 * buf	| buffer
 * fmt	| format
 * sz	| size
 * wc	| wide char
 * c	| char
 */



/*
 * Color >_<
 */

enum color_value{
	BLACK = 0,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	CYAN,
	WHITE
};

unsigned char mkcolor(enum color_value fg, enum color_value bg){
	return (fg << 4) | bg;
}



/*
 * Icons... :<
 */

#include <stdio.h>

#if UNICODE_SUPPORT == 1

/*
 * Use external library for support.
 */

#include <wchar.h>

#else

/*
 * Default the wide types into their normal counterparts.
 */

typedef int wint_t;
typedef char wchar_t;

static wint_t putwchar(wchar_t wc){
	return putchar(wc);
}

#endif /* UNICODE_SUPPORT */

/*
 * Accepts both char and wchar_t.
 * "vc" stands for "varied character" and "type" expects values from enum
 * vc_type.
 */

enum vc_type{
	VC_CHAR,
	VC_WIDE
};

int putvchar(int vc, enum vc_type t){
	int val = 0;
	switch(t){
	case VC_CHAR:
		val = putchar(vc);
		break;
	case VC_WIDE:
		val = putwchar(vc);
		break;
	default:
		break;
	}
	return val;
}

/* TODO: continue supporting unicode and ascii characters! */



/*
 * The screen!
 */

enum screen_type{
	SLIM = 0,
	WIDE,
};

struct screen{
	enum screen_type type;
	unsigned char *color_array;
	void *icon_array;
};
