#ifndef _TEST_H
#define _TEST_H

#if 0
/* [ TEST 0 ] */
int gm(int val){
	int in = 0;
	uint16_t ico = 0;
	clearscr();
	do{
		system("clear");
		putscr();
		in = input();
		switch(in){
		case 'a':
			ico = mkscrico(CLRCYN, CLRBLK, 1,
					'#');
			break;
		case 'w':
			ico = mkscrico(CLRGRN, CLRBLK, 1,
					'#');
			break;
		case 's':
			ico = mkscrico(CLRYLW, CLRBLK, 1,
					'#');
			break;
		case 'd':
			ico = mkscrico(CLRPUR, CLRBLK, 1,
					'#');
			break;
		}
		setscrico(ico, 1, 1);
	}while(in != 'x');
	return 0;
}
#endif

#if 1
/* [ TEST 1 ] */
int gm(int val){
	int in = 0;
	uint16_t ico = 0;
	clearscr();
	do{
		system("clear");
		putscr();
		in = input();
		switch(in){
		case 'a':
			ico = mkscrico(CLRCYN, CLRBLK, 1,
					'#');
			break;
		case 'w':
			ico = mkscrico(CLRGRN, CLRBLK, 1,
					'#');
			break;
		case 's':
			ico = mkscrico(CLRYLW, CLRBLK, 1,
					'#');
			break;
		case 'd':
			ico = mkscrico(CLRPUR, CLRBLK, 1,
					'#');
			break;
		}
		setscrico(ico, 1, 1);
	}while(in != 'x');
	return 0;
}
#endif

#endif
