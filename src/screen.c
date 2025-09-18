#include "screen.h"
#include <stdint.h>
#include <stdio.h>


/*
 * We need to color an icon, which is a part
 * of a screen.
 */

enum screen_color{
	SCREEN_BLACK = 0,
	SCREEN_GREEN,
	SCREEN_YELLOW,
	SCREEN_BLUE,
	SCREEN_PURPLE,
	SCREEN_CYAN,
	SCREEN_WHITE
};

#define set_color_foreground(_color,	\
		_foreground)	\
		(_color |= (uint8_t)_foreground << 4)

#define set_color_background(_color,	\
		_background)	\
		(_color |= (uint8_t)_background << 4)

static uint8_t make_color(
		enum screen_color foreground,
		enum screen_color background){
	uint8_t color = 0;
	set_color_foreground(color, foreground);
	set_color_background(color, background);
	return color;
}

#define get_color_foreground(_color)	\
	(_color >> 4)

#define get_color_background(_color)	\
	(_color & 0x0f)

static int put_color_foreground(
		enum screen_color foreground){
	if(printf("\033[3%d", foreground) == EOF)
		return -1;
	return 0;
}

static int put_color_background(
		enum screen_color background){
	if(printf("\033[3%d", background) == EOF)
		return -1;
	return 0;
}

static int put_color(uint8_t color){
	if(put_color_foreground(
				get_color_foreground(color))
			!= 0)
		return -1;
	if(put_color_background(
				get_color_background(color))
			!= 0)
		return -2;
	return 0;
}


/*
 * We also need a symbol for the icon to
 * display.
 */

#define set_symbol_glow(_symbol, _glow)	\
	((uint8_t)_symbol |=	\
	 ((uint8_t)_glow << 7))

#define set_symbol_value(_symbol, _value)	\
	((uint8_t)_symbol |= (uint8_t)_value)

static uint8_t make_symbol(uint8_t glow,
		uint8_t value){
	uint8_t symbol = 0;
	set_symbol_glow(symbol, glow);
	set_symbol_value(symbol, value);
	return symbol;
}

#define get_symbol_glow(_symbol)	\
	((uint8_t)_symbol >> 7)

#define get_symbol_value(_symbol)	\
	((uint8_t)_symbol & 0x7f)

static int put_symbol_glow(uint8_t glow){
	if(printf("\033[%dm", glow) == EOF)
		return -1;
	return 0;
}

static int put_symbol_value(uint8_t value){
	if(putchar(value) == EOF)
		return -1;
	return 0;
}

static int put_symbol(uint8_t symbol){
	if(put_symbol_glow(
				get_symbol_glow(symbol)) != 0)
		return -1;
	if(put_symbol_value(
				get_symbol_value(symbol))
			!= 0)
		return -2;
	return 0;
}


/*
 * And finally, the icon, a part of the
 * screen.
 */

#define set_icon_color(_icon, _color)	\
	((uint8_t)_icon |= (uint8_t)_color << 8)

#define set_icon_symbol(_icon, _symbol)	\
	((uint8_t)_icon |= (uint8_t)_symbol << 8)

static uint16_t make_icon(uint8_t color,
		uint8_t symbol){
	uint16_t icon = 0;
	set_icon_color(icon, color);
	set_icon_symbol(icon, symbol);
	return icon;
}

/* TODO */
