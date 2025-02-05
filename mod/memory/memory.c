#include "./memory.h"
#include "./string.h"

#define MEMORY_TOP	&(memory_map[MEMORY_SIZE - 1])
#define MEMORY_BLKMAX	16

static unsigned char memory_map[MEMORY_SIZE];
static unsigned char *memory_ptr;

static struct blk{
	void **blkptr;
	unsigned long size;
};

static struct blk memory_blktable[MEMORY_BLKMAX];

static struct blk blk_default = {0, MEMORY_SIZE};

void memory_reset(void){
	unsigned long i = 0;
	while(i < MEMORY_SIZE){
		memory_map[i] = 0;
		i++;
	}
	memory_ptr = MEMORY_TOP;
	i = 0;
	while(i < MEMORY_BLKMAX){
		memory_blktable[i] = blk_default;
		i++;
	}
	return;
}

int findblkn(unsigned long nmemb){
	int n = 0;
	while(memcmp(&(memory_blktable[n]), &blk_default, sizeof(struct blk)) == 1 && n < MEMORY_BLKMAX){
		n++;
	}
	if(n == MEMORY_BLKMAX){
		return -1;
	}
	return n;
}

int blkalloc(unsigned long nmemb, unsigned long align, void **ptr){
	struct blk blkinfo;
	unsigned long blksize;
	int blknum;
	if(nmemb == 0 || align == 0 || ptr == 0){
		return -1;
	}
	blksize = nmemb + (nmemb % align);
	blknum = findblkn(blksize);
	if(blknum == -1){
		return -1;
	}
	if((memory_ptr - blksize) < memory_map){
		return -1;
	}
	memory_ptr -= blksize;
	blkinfo.blkptr = ptr;
	blkinfo.size = blksize;
	memory_blktable[blknum] = blkinfo;
	return 0;
}
