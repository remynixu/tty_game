#include "./mod/display/window.h"

#define ENTRY_NAME	main
#define NULL		((void *)0)

extern void test0(void);

int ENTRY_NAME(void){
	test0();
	color_cleanup();
	return 0;
}
