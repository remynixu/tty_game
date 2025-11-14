#include <stdio.h>
#include "framework/block.h"

int main(void){
	char test[100] = {0};
	void *blk = blkfmt(test, 100);
	char *ptr = blkalloc(blk, 10);
	printf("yay! | %p | %p |\n", blk, ptr);
	*ptr = 'L';
	printf("%c\n", *ptr);
	blkfree(blk, ptr);
	printf("yay! | %p | %p |\n", blk, ptr);
	return 0;
}
