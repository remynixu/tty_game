#include "./memory.h"
#include "./mod_macro.h"

static unsigned char stack_memory[STACKMEM_SIZE] = {0};
static unsigned char *stackmem_ptr = &stack_memory[STACKMEM_SIZE - 1];

unsigned long diff_sp(void){
	return stackmem_ptr - &stack_memory[STACKMEM_SIZE - 1];
}

void *balloc(unsigned long nmemb){
	stackmem_ptr += nmemb;
	return stackmem_ptr;
}
