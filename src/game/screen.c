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
 * - Character - An ASCII character.
 *
 * The dimensions of the array is defined by:
 * - SCREEN_WIDTH  - The size of the row to display in the terminal.
 * - SCREEN_HEIGHT - The size of the column to display in the terminal.
 */

/*
 * Abbreviated terms:
 * scr	| screen
 * pos	| position
 * val	| value
 * str	| string
 * buf	| buffer
 * fmt	| format
 * sz	| size
 * fg	| foreground
 * bg	| background
 * c	| char
 */



/*
 * Colors! >o<
 */

#include "framework/memory.h"

enum color_val{
	BLACK = 0,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	CYAN,
	WHITE
};

static uint8_t mkcolor(enum color_val fg, enum color_val bg){
	return (fg << 4) | bg;
}

static enum color_val getfg(uint8_t color){
	return color >> 4;
}

static enum color_val getbg(uint8_t color){
	return color & 0x0f;
}

#define COLOR_STRLEN	8 /* \033[30;40m */
#define COLOR_FG_INDEX	3
#define COLOR_BG_INDEX	6

static char itoc(int i){
	return i + '0';
}

static char *color_to_str(uint8_t color, char str[COLOR_STRLEN]){
	memcpy(str, "\033[30;40m");
	str[COLOR_FG_INDEX] = itoc(getfg(color));
	str[COLOR_BG_INDEX] = itoc(getbg(color));
	return str;
}
