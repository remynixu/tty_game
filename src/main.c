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
