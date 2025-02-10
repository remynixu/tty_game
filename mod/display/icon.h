#ifndef ICON_H
#define ICON_H

/* dont worry about colored bytes again ;) */

struct icon{
	unsigned char packed_clr;
	char graphic_byte;
};

extern struct icon mkicon(unsigned char packed_clr, char graphic_byte);
extern int puticon(struct icon icon);

#endif /* ICON_H */
