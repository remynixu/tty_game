#ifndef MEMORY_H
#define MEMORY_H

/*
 * Just a cute interface for memory stuff XD
 */

/* Constants! :] */
#include "presets.h"



/*
 * The memory allocating functions, self-explanatory, functions like the
 * stdlib.h counterparts.
 */

void *memalloc(size_t sz);
void *memrealloc(void *ptr, size_t sz);
void memfree(void *ptr);

/*
 * These are for managing memories instead.
 */

void *memcpy(void *dest, void *src, size_t sz);
void *memset(void *dest, uint8_t src, size_t sz);



#endif /* MEMORY_H */
