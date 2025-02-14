#ifndef CLR_H
#define CLR_H

/* preserve color id constants to prevent wormhole. */

enum clr_id{
	CID_BLACK	= 0x00,
	CID_RED		= 0x01,
	CID_GREEN	= 0x02,
	CID_YELLOW	= 0x03,
	CID_BLUE	= 0x04,
	CID_PURPLE	= 0x05,
	CID_CYAN	= 0x06,
	CID_WHITE	= 0x07
};

#ifndef __NOCLR

/* returns a valid color, its not expected that this
 * function will ever fail other than you. */

extern char mkclr(char fg, char bg);

/* put color on terminal, return 0 on success, OUT_ERR
 * on fail. */

extern char putclr(char clr);

/* if colors dont exist, turn the functions to no ops */
#else

#define mkclr(fg, bg)	do{}while(0)
#define putclr(clr)	do{}while(0)

#endif /* __NOCLR */

#endif /* CLR_H */
