#ifndef WND_H
#define WND_H

#include "../lib/def.h"

#define WNDENOMEM	0xff

extern uint8_t getwid(void);
extern char putwnd(uint8_t wid);
extern void wputc(uint8_t wid, char c,
		uint8_t x, uint8_t y);

#endif /* WND_H */
