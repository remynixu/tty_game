#include "./game/assets/obj.h"
#include "./game/assets/snd.h"
#include "./tty/scrbuf.h"

int main(void){
	struct obj obj;
	clrsb();
	obj.id = 1;
	obj.x = 3;
	obj.y = 7;
	sbputobj(obj);
	putsb();
	snd_beep(SNDBEEP_MED, 1.0);
	return 0;
}
