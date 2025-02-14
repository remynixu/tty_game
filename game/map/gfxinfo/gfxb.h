#ifndef GFXB_H
#define GFXB_H

/* only storing the information about what to display is
 * more compact and memory friendly. */

struct gfxb{
#ifndef __NOCLR
	char clr;
#endif /* __NOCLR */
	char icon;
};

/* see clr.h and icon.h for mkgfxb() parameter
 * explanation.
 *
 * returns a valid gfxb, again, this is not expected to
 * fail and return invalid values but only through you,
 * you should be careful. */

extern struct gfxb mkgfxb(char clr, char icon);

/* put a gfxb on terminal, returns 0 on success,
 * OUT_ERR on failure. */

extern char putgfxb(struct gfxb gfxb);

#endif /* GFXB_H */
