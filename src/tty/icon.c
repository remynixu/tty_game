#include "./icon.h"
#include "./io/out.h"

static char icon_table[ICONID_MAX] = {
	'?',
	' ',
	'#'
};

char puticon(char id){
	if(putb(icon_table[id]) == OUT_ERR){
		return OUT_ERR;
	}
	return 0;
}
