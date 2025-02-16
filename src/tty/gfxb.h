#ifndef GFXB_H
#define GFXB_H

/* we need to abstract the *unknown* implementation
 * away from the game, only providing limited
 * guaranteed looks in the form of id's.
 * 
 * we do not have our own id's, we rely on icon.h for
 * the id's. we are just adding colors to it afterall,
 * we also let the user decide if we compile without
 * color anyways... */

#define GFXBID_MAX	2

extern char putgfxb(char icon_id);

#endif /* GFXB_H */
