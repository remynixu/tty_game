#ifndef CLR_H
#define CLR_H

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

/* returns a valid color, its not expected that this
 * function will ever fail other than you. */

extern char mkclr(char fg, char bg);

/* put color on terminal, return 0 on success, OUT_ERR
 * on fail. */

extern char putclr(char clr);

#endif /* CLR_H */
