#ifndef MATH_H
#define MATH_H

/* we dont like our char be going anywhere, it should
 * only be positive values only, no matter what. */

#define abs(x)		((x) & 0x7f)
#define absmin(x, y) \
	(abs(x) < abs(y) ? abs(x) : abs(y))
#define absmax(x, y) \
	(abs(x) > abs(y) ? abs(x) : abs(y))

/* because we only work with char as base data type.. */

#define ABSMAX		abs((char)0xff)

#endif /* MATH_H */
