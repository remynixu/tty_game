#ifndef SCRBUF_H
#define SCRBUF_H

#include "../lib/def.h"

extern uint16_t tosbpos(uint8_t x, uint8_t y);

extern int putsbrow(uint8_t y);
extern int putsb(void);

extern void clrsb(void);
extern void sbputc(char c, uint16_t sbpos);
extern void sbputclr(uint8_t clr,
		uint16_t sbpos);

#endif /* SCRBUF_H */
