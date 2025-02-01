#include "./mod/mod_macro.h"

extern void memory_test0(void);

int ENTRY_NAME(void){
	memory_test0();
	return 0;
}
