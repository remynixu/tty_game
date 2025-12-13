#include "memory.h"
#include <stdlib.h>

void *memalloc(size_t sz){
	return malloc(sz);
}

void *memrealloc(void *ptr, size_t sz){
	return realloc(ptr, sz);
}

void memfree(void *ptr){
	free(ptr);
}

void *memcpy(void *dest, void *src, size_t sz){
	uint8_t *__dest = dest;
	uint8_t *__src = src;
	for(; sz != 0; __dest++, __src++, sz--)
		*__dest = *__src;
	return dest;
}

void *memset(void *dest, uint8_t src, size_t sz){
	uint8_t *__dest = dest;
	for(; sz != 0; __dest++, sz--)
		*__dest = src;
	return dest;
}
