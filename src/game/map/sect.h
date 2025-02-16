#ifndef SECTOR_H
#define SECTOR_H

#define SECTORWIDTH	40
#define SECTORHEIGHT	20
#define SECTORSIZE	(SECTORWIDTH * SECTORHEIGHT)

struct sector{
	char obj_id[SECTORSIZE];
};

extern char putsector(struct sector *sector);

#endif /* SECTOR_H */
