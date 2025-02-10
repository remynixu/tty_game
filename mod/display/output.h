#ifndef OUTPUT_H
#define OUTPUT_H

/* we need a way to make output changing easier. */

#include <stdio.h>

#define putb(c)		putchar((c))
#define O_ERR		EOF

extern int printb(char *str);

#endif /* OUTPUT_H */
