#ifndef CLR_H
#define CLR_H

#include "../lib/def.h"

enum clr_id{
	CID_BLACK,
	CID_RED,
	CID_GREEN,
	CID_YELLOW,
	CID_BLUE,
	CID_PURPLE,
	CID_CYAN,
	CID_WHITE
};

extern uint8_t mkclr(enum clr_id fg,
		enum clr_id bg);
extern uint8_t putclr(uint8_t clr);

#endif /* CLR_H */
