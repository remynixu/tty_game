#include <stdio.h>
#include "framework/block.h"

int main(void){
	char test[100];
	char msg[100] = {0};
	void *blk = blkfmt(test, 100);
	void *ptr1 = blkalloc(blk, 10); 
	void *ptr2 = blkalloc(blk, 10); 
	void *ptr3 = blkalloc(blk, 1);
	blkdump(blk, putchar, 8);
	return 0;
}
