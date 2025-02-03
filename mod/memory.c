#include "./memory.h"

#define STACKMEM_SIZE	(16 * 1024)
#define STACKMEM_TOP	&(stackmem_map[STACKMEM_SIZE - 1])

static unsigned char stackmem_map[STACKMEM_SIZE];
static unsigned char *stackmem_ptr = STACKMEM_TOP;

void *blkalloc(unsigned long nmemb, unsigned long align){
	unsigned long sp_finalpos;
	if(nmemb == 0 || align == 0){
		return 0;
	}
	sp_finalpos = nmemb + (nmemb % align);
	if((stackmem_ptr - sp_finalpos) < stackmem_map){
		return 0;
	}
	stackmem_ptr -= sp_finalpos;
	return stackmem_ptr;
}
