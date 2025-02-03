#include "./mod/memory.h"
#include "./mod/display/window.h"

#include <stdio.h>

void memory_test0(void){
	char *str = 0;
	char *str2 = 0;
	printf("%lu\n", diff_sp());
	str = balloc(5);
	str[0] = 'l';
	str[1] = 'm';
	str[2] = 'a';
	str[3] = 'o';
	str[4] = '\0';
	printf("%lu\n", diff_sp());
	printf("%s\n", str);
	str2 = balloc(5);
	str2[0] = '1';
	str2[1] = '3';
	str2[2] = '2';
	str2[3] = '0';
	str2[4] = '\0';
	printf("%lu\n", diff_sp());
	printf("%s\n", str2);
	return;
}

void memory_test1(void){
	struct color *clr = 0;
	int retval = 0;
	clr = balloc(sizeof(struct color));
	if(clr == 0){
		printf("-%i-\n", retval);
		return;
	}
	clr->attr = CATTR_INVERSE;
	clr->fg = CID_RED;
	clr->bg = CID_BLACK;
	if((retval = fput_color(stdout, clr)) != 0){
		printf("-%i-\n", retval);
		return;
	}
	printf("Hello world!\n");
	return;
}

static struct window *wnd = NULL;
static struct color clr = {CATTR_RESET, CID_RED, CID_BLACK};
static struct gridbox gbox = {&clr, '?'};

void test0(void){
	int i = 0;
	int retval = 0;
	wnd = balloc(sizeof(struct window));
	if(wnd == NULL){
		printf("-%i-\n", retval);
		return;
	}
	wnd->width = 40;
	wnd->height = 20;
	wnd->gboxes = balloc(sizeof(struct gridbox) * (wnd->width * wnd->height));
	if(wnd->gboxes == NULL){
		retval = 1;
		printf("-%i-\n", retval);
		return;
	}
	while(i < wnd->width * wnd->height){
		wnd->gboxes[i] = gbox;
		i++;
	}
	if((retval = fput_wnd(stdout, wnd)) != 0){
		printf("-%i-\n", retval);
		return;
	}
	return;
}
