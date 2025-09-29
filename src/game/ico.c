#include "ico.h"
#include <stdint.h>



/*
 * - An icon (ico) is an entry with a position
 * on the screen and hitbox management.
 * The format is:
 * [ pos | hb | etr] & [ 8 | 8 | 16 ]
 */

#define ldpos(ico, p)	(ico | (p << 24))
#define ldhb(ico, hb)	(ico | (hb << 16))
#define ldetr(ico, e)	(ico | e)

#define mkico(p, hb, e)	\
	ldetr(ldhb(ldpos(0, p), hb), e)

#define frpos(ico)	((ico >> 24) & 0xff)
#define frhb(ico)	((ico >> 16) & 0xff)
#define fretr(ico)	(ico & 0xffff)

/* -- A position (pos) consists of two
 * properties:
 * > x - The horizontal position.
 * > y - The vertical position.
 * Where the format is:
 * [ x | y ] & [ 4 bits | 4 bits ]
 */

#define ldx(pos, x)	(pos | (x << 4))
#define ldy(pos, y)	(pos | y)

#define mkpos(x, y)	ldy(ldx(0, x), y)

#define frx(pos)	(pos >> 4)
#define fry(pos)	(pos & 0xf)

/* -- A hitbox (hb) is what's used to keep
 * each icon unique and different from each
 * other. The format is:
 * [ sw | id ] & [ 1 | 7 ]
 */

#define ldsw(hb, sw)	(hb | (sw << 7))
#define ldid(hb, id)	(hb | id)

#define mkhb(sw, id)	ldid(ldsw(0, sw), id)

#define frsw(hb)	(hb >> 7)
#define frid(hb)	(hb & 0x7f)

/* 7 bits means that there's only 127 - 1
 * icons that could be tracked.
 * The 127th value is used for static icons.
 *
 * These values will be used to track the
 * icons' hitboxes, which will be done through
 * automatic handling rather than manual.
 */

/* TODO */
