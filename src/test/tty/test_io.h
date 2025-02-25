#include "../../tty/io.h"

#define test_io() { \
	putb(pollb()); \
	printstr("help me\n"); \
}
