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
