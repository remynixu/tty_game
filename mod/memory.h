#ifndef MEMORY_H
#define MEMORY_H	1

#include <stdio.h>

extern void *balloc(unsigned long nmemb);
extern unsigned long diff_sp(void);

#endif /* MEMORY_H */
