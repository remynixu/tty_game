#ifndef MEMORY_H
#define MEMORY_H

/*
 * Just a cute interface for memory stuff XD
 */

/* Constants! :] */
#include "presets.h"



/*
 * The memory functions, self-explanatory, functions like the stdlib.h
 * counterparts.
 */

void *memalloc(size_t sz);
void *memrealloc(void *ptr, size_t sz);
void memfree(void *ptr);



#endif /* MEMORY_H */
