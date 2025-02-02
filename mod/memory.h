#ifndef MEMORY_H
#define MEMORY_H	1

#include <stdio.h>

#define STACKMEM_SIZE	((unsigned short)-1)
#define STACKMEM_ALIGN	8
#define STACK_PTRMAX	(STACKMEM_SIZE / STACKMEM_ALIGN)

extern void *balloc(unsigned long nmemb);
extern unsigned long diff_sp(void);

#endif /* MEMORY_H */
