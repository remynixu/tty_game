#include "screen.h"

int main(void){
	fillscr(mkicon(1, '?', ICON_RED,
				ICON_BLACK));
	putscr();
	return 0;
}
