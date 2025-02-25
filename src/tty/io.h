#ifndef IO_H
#define IO_H

#include "../lib/def.h"

#define IO_ERR		0xff

extern char putb(char c);
extern char printstr(char *str);

extern char pollb(void);

#endif /* IO_H */
