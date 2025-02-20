#ifndef CLR_H
#define CLR_H

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

extern unsigned char mkclr(enum clr_id fg,
		enum clr_id bg);
extern int putclr(unsigned char clr);

#endif /* CLR_H */
