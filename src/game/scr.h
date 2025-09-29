#ifndef SCR_H
#define SCR_H

#include <stdint.h>



/*
 * - A screen (scr) is made up of entries.
 * It's dimensions are defined by macros:
 * SCRW and SCRH.
 */

#define SCRW	20
#define SCRH	10

void flushscr(void);

/*
 * [] Returns:
 * > 0 on success.
 * > (< 0) on failure.
 */

int scrput(uint16_t etr, uint8_t x,
		uint8_t y);

/*
 * [] Returns:
 * > An entry (etr) on success.
 * > ETRERR on failure.
 */

uint16_t scrget(uint8_t x, uint8_t y);

int putscr(void);

/*
 * So it's byte size is: 16 * SCRW * SCRH.
 *
 * -- An entry (etr) is made up of a color, an
 * ascii character, and a glow. It's bit size
 * is: 4 + 4 + 7 + 1 = 16. Entry bit format:
 * [ fg | bg | glow | char ]
 */

/*
 * [] All Returns:
 * > Modified entry (etr).
 */

#define ldfg(etr, fg)	\
	(etr | (((uint16_t)fg & 0xf) << 12))
#define ldbg(etr, bg)	\
	(etr | (((uint16_t)bg & 0xf) << 8))
#define ldg(etr, g)	\
	(etr | (((uint16_t)g & 0x1) << 7))
#define ldc(etr, c)	\
	(etr | ((uint16_t)c & 0x7f))

/*
 * [] Returns:
 * > An entry.
 */

#define mketr(fg, bg, g, c)	\
	ldc(ldg(ldbg(ldfg(0, fg), bg), g), c)

#define ETRERR	0x5555

/*
 * [] All Returns:
 * > Part of an entry (etr).
 */

#define frfg(etr)	((etr >> 12) & 0xf)
#define frbg(etr)	((etr >> 8) & 0xf)
#define frg(etr)	((etr >> 7) & 0x1)
#define frc(etr)	(etr & 0x7f)

/*
 * [] Returns:
 * > 0 on success.
 * > EOF on failure.
 */

int putetr(uint16_t etr);

/*
 * --- A color (clr) has foreground and
 * background. It's values are assigned by
 * enum color_value.
 */

enum color_value{
	CLRBLK = 0,
	CLRRED,
	CLRGRN,
	CLRYLW,
	CLRBLU,
	CLRPUR,
	CLRCYN,
	CLRWHT
};

/*
 * ---- A foreground (fg) refers to the color
 * of the ascii character. It only has 8
 * values, meaning it fits in just 4 bits.
 */

/*
 * [] Returns:
 * > 0 on success.
 * > EOF on failure.
 */

int putfg(enum color_value fg);

/*
 * ---- A background (bg) refers to the color
 * around the ascii character. It only has 8 
 * values, meaning it fits in just 4 bits.
 */

/*
 * [] Returns:
 * > 0 on success.
 * > EOF on failure.
 */

int putbg(enum color_value bg);

/*
 * --- An ascii character (c) is a graphical
 * character from the ascii character chart.
 * It has less than 128 valid values, so it
 * fits in just 7 bits.
 */

/* putchar() is used for ascii characters. */

/*
 * --- A glow is just a single bit that tells
 * if an entry has extra brightness or not.
 * It only has 2 values, it fits in 1 bit.
 */

/*
 * [] Returns:
 * > 0 on success.
 * > EOF on failure.
 */

int putg(int g);

/*
 * - A subscreen (subscr) is a two dimensional
 * array of entries you can manipulate in
 * the screen.
 * It's dimensions are dynamic, controlled by:
 * > x - The x position of the subscreern in
 *     the screen.
 * > y - The y position of the subscreen in
 *     the screen.
 * > w - The width of the controlled entries.
 * > h - The height of the controlled entries.
 */

struct subscr{
	uint8_t x;
	uint8_t y;
	uint8_t w;
	uint8_t h;
	uint16_t *etrarr;
};

#include <stdlib.h>

/*
 * [] Returns:
 * > Enough memory for requested entry size.
 * > NULL on failure.
 */

#define _etralloc(n)	\
	malloc(sizeof(uint16_t) * (n))

/*
 * [] Returns:
 * > 0 on success.
 * > ENOMEM on failure.
 */

int initsubscr(struct subscr *ss, uint8_t x,
		uint8_t y, uint8_t w, uint8_t h);
void fillsubscr(struct subscr *ss,
		uint16_t etr);
void flushsubscr(struct subscr *ss);

/*
 * [] Returns:
 * > 0 on success.
 * > (< 0) if problems occured.
 */

int subscrput(struct subscr *ss, uint16_t etr,
		uint8_t x, uint8_t y);

/*
 * [] Returns:
 * > An entry (etr) on success.
 * > ETRERR on failure.
 */

uint16_t subscrget(struct subscr *ss,
		uint8_t x, uint8_t y);

/*
 * Note that this doesn't write to stdout.
 * Rather, it writes to the screen instead.
 */

/*
 * [] Returns:
 * > 0 on success.
 * > (< 0) if problems occured.
 */

int putsubscr(struct subscr *ss);



#endif
