#include "../../tty/clr.h"
#include "./test_io.h"

#define test_clr() { \
	putclr(mkclr(CID_RED, CID_BLACK)); \
	test_io(); \
}
