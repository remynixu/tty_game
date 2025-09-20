#include "gm.h"
#include "scr.h"
#include <stdio.h>
#include <stdlib.h>



static int input(void){
	int in = '\n';
	while(in == '\n')
		in = getc(stdin);
	return in;
}

static struct subscr menu = {0};

static int init(void){
	clearscr();
	if(mksubscr(&menu, SCRWIDTH, 3, 0, 0)
			!= 0)
		return -1;
	fillsubscr(&menu, mkscrico(CLRWHT, CLRBLK,
				0, '#'));
	return 0;
}

static int refresh(void){
	if(system("clear") != 0)
		return -1;
	loadsubscr(&menu);
	putscr();
	return 0;
}

int gm(int val){
	int in = 0;
	if(init() != 0)
		return -1;
	do{
		if(refresh() != 0)
			return -1;
		in = input();
	}while(in != 'x');
	return 0;
}
