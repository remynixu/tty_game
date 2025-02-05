/* I swear im not reinventing the wheel, im only
 * doing this because not all platform has stdio.h. */

#ifndef IO_H
#define IO_H		1

#ifndef __no_stdio

#include <stdio.h>

/* putb() *must* put a graphic byte on the screen
 * and the next call *must* put a byte *adjacent* to it
 * or to the *next line*.
 *
 * the required return value is either the byte "put" or
 * IO_ERR on failure. */

#define putb(byte)	putchar((byte))
#define IO_ERR		EOF

#else

/* insert custom library here (preferably on ./io directory).
 * do note that you must also provide what the
 * top directive provided i.e putb(), IO_ERR, etc...
 *
 * also follow the behavior listed above. */

#include

#define putb(byte)
#define IO_ERR

#endif /* !__no_stdio */

/* print multiple bytes in order.
 * returns count of bytes printed or IO_ERR on failure. */

extern int printb(char *bytes);

#endif /* IO_H */
