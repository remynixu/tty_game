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

/* we need mkclr to turn the clr_id's to comprehendable
 * (implementation-wise) data for putclr().
 *
 * arrays wont do the trick here, they shouldnt, they
 * WILL NOT. */

extern char mkclr(char cid_fg, char cid_bg);
extern char putclr(char clr);

#else

#define mkclr(cid, cid)	0
#define putclr(clr)	0

#endif /* __NOCLR */

#endif /* CLR_H */
