#include "./gridbox.h"

int isvalgbox(struct gridbox gbox){
	if(isvalclr(gbox.clrinfo) == 0 || gbox.icon == 0){
		return 0;
	}
	return 1;
}

int fputgbox(FILE *f, struct gridbox gbox){
	int retval;
	int printedbnum = 0;
	if(isvalgbox(gbox) == 0){
		retval = EOF;
		goto out;
	}
	retval = fputclr(f, gbox.clrinfo);
	if(retval == EOF){
		goto out;
	}
	printedbnum = fputc(gbox.icon, f);
	if(printedbnum == EOF){
		goto out;
	}
	retval += printedbnum;
out:
	return retval;
}
