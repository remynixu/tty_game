#include "./color.h"

#define ID_MAX		0x7
#define ATTR_MAX	0x1

#define ID_BITSIZE	0x3
#define ATTR_BITSIZE	0x1

#define BG_OFFSET	0x0
#define FG_OFFSET	(ID_BITSIZE + BG_OFFSET)
#define ATTR_OFFSET	(ID_BITSIZE + FG_OFFSET)

unsigned char getbytebitn(unsigned char byte, unsigned char nmemb, unsigned char offset){
	return ((byte << (sizeof(unsigned char) - nmemb - offset)) >> (sizeof(unsigned char) - nmemb - offset));
}

int isvalclr(unsigned char clr){
	int retval;
	/* gingus - BONErr */
	if(getbytebitn(clr, ID_BITSIZE, BG_OFFSET) > ID_MAX){
		retval = 0;
		goto out;
	}
	if(getbytebitn(clr, ID_BITSIZE, FG_OFFSET) > ID_MAX){
		retval = 0;
		goto out;
	}
	if(getbytebitn(clr, ATTR_BITSIZE, ATTR_OFFSET) > ATTR_MAX){
		retval = 0;
		goto out;
	}
	retval = 1;
out:
	return retval;
}

unsigned char mkclr(enum color_attr attr, enum color_id fg, enum color_id bg){
	unsigned char retval;
	if(attr > ATTR_MAX){
		retval = 0;
		goto out;
	}
	if(fg > ID_MAX){
		retval = 0;
		goto out;
	}
	if(bg > ID_MAX){
		retval = 0;
		goto out;
	}
	retval = 0;
	retval |= (attr << ATTR_OFFSET);
	retval |= (fg << FG_OFFSET);
	retval |= (bg << BG_OFFSET);
out:
	return retval;
}

int fputclr(FILE *fstream, unsigned char clr){
	int retval;
	char clrstr[] = "\001\033[0;30;40m\002";
	if(isvalclr(clr) == 0){
		retval = EOF;
		goto out;
	}
	clrstr[3] = getbytebitn(clr, ATTR_BITSIZE, ATTR_OFFSET);
	clrstr[6] = getbytebitn(clr, ID_BITSIZE, FG_OFFSET);
	clrstr[9] = getbytebitn(clr, ID_BITSIZE, BG_OFFSET);
	retval = fputs(clrstr, fstream);
	if(retval == EOF){
		goto out;
	}
out:
	return retval;
}
