#include "./memory.h"

#define NULL		((void *)0)
#define STACKMEM_TOP	&stack_memory[STACKMEM_SIZE - 1]

static unsigned char stack_memory[STACKMEM_SIZE] = {0};
static unsigned char *stackmem_ptr = STACKMEM_TOP;
static unsigned char *stack_ptrtable[STACK_PTRMAX] = {0};

void bclean(int blk_i0, int blk_i1){
	unsigned char *sptop = NULL;
	unsigned char *spbot = NULL;
	if((blk_i0 | blk_i1) == 0){
		sptop = STACKMEM_TOP;
		spbot = stack_ptrtable[blk_i0];
	}
	else{
		sptop = stack_ptrtable[blk_i1];
		spbot = stack_ptrtable[blk_i0];
	}
	if(sptop == spbot){
		/* why did the user allocate nothing?
		 * who knows? */
		*sptop = 0;
		return;
	}
	while(spbot != sptop){
		/* who cares if spbot is actually at the top?
		 * just work! */
		*spbot = 0;
		if(spbot < sptop){
			spbot++;
		}
		else{
			spbot--;
		}
	}
	return;
}

int isvalbptr(void *ptr, int *blk_i){
	/* let's just crash if blk_i == NULL */
	while(*blk_i < STACK_PTRMAX){
		if(ptr == stack_ptrtable[*blk_i]){
			return 1;
		}
		*blk_i += 1;
	}
	return 0;
}

int find_emptyblk(void){
	int blk_i = 0;
	while(blk_i < STACK_PTRMAX){
		if(stack_ptrtable[blk_i] == NULL){
			return blk_i;
		}
		blk_i++;
	}
	return -1;
}

unsigned long diff_sp(void){
	if(stackmem_ptr < STACKMEM_TOP){
		return STACKMEM_TOP - stackmem_ptr;
	}
	return stackmem_ptr - STACKMEM_TOP;
}

void *balloc(unsigned long nmemb){
	int blk_i = find_emptyblk();
	if(nmemb > STACKMEM_SIZE){
		return NULL;
	}
	if(blk_i == -1){
		return NULL;
	}
	stackmem_ptr += nmemb;
	stack_ptrtable[(unsigned int)blk_i] = stackmem_ptr;
	return stackmem_ptr;
}

void bfree(void *ptr){
	int blk_i = 0;
	if(isvalbptr(ptr, &blk_i) == 0){
		return;
	}
	if(blk_i == 0){
		bclean(0, 0);
	}
	else{
		bclean(blk_i, blk_i - 1);
	}
	return;
}
