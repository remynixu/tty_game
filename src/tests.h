#if 0

#include "screen.h"
int main(void){
	struct icon buf[5 * 5] = {0};
	struct window wnd = {
		buf,
		5, 5,
		4, 4,
	};
	struct icon ico = {
		mksym('#'),
		mkci(CLRRED, CLRBLK),
		1
	};
	fillwnd(&wnd, ico);
	clearscr();
	putwnd(&wnd);
	putscr();
	return 0;
}

#endif

#if 0

#include "screen.h"
int main(void){
	struct icon ico;
	ico = mkico('#', CLRCYN, CLRBLK, 1);
	clearscr();
	stackonly_mkwnd(wnd, ico, 4, 4, 4, 4);
	putwnd(&wnd);
	putscr();
	return 0;
}

#endif
