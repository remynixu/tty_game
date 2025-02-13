#include "./icon.h"
#include "../../../tty/out.h"

char puticon(char icon){
	if(putb(icon) == OUT_ERR){
		return OUT_ERR;
	}
	return 0;
}
