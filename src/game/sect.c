#include "./sect.h"

static char icons_table[8][800];
static unsigned char clrs_table[8][800];
static struct sect secttable[8];
static unsigned char bitmap = 0;

struct sect *sectalloc(void){
	unsigned char bitmap_index = 0;
	while(bitmap & (1 << bitmap_index)){
		if(bitmap_index >= 8){
			return 0;
		}
		bitmap_index++;
	}
	secttable[bitmap_index].icons =
		icons_table[bitmap_index];
	secttable[bitmap_index].clrs =
		clrs_table[bitmap_index];
	bitmap |= 1 << bitmap_index;
	return &secttable[bitmap_index];
}
