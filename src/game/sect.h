#ifndef SECT_H
#define SECT_H

struct sect{
	char *icons;
	unsigned char *clrs;
};

/* where would the sector come from?
 * here! */

/*
 * @brief - sectalloc()
 * - allocates memory big enough for a sector.
 * @return
 * - success: allocated sector
 * - fail: 0
 */
extern struct sect *sectalloc(void);

/*
 * @brief - putsect()
 * - puts a sector on screen.
 */
extern void putsect(struct sect *sect);

#endif /* SECT_H */
