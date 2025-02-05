/* only doing this because stdlib.h isnt expected to
 * be everywhere. */

#ifndef MEMORY_H
#define MEMORY_H	1

#define KILOBYTE	1024

/* you should probably set this low if the system doesnt
 * have much to begin with. */

#define MEMORY_SIZE	(64 * KILOBYTE)

extern int blkalloc(unsigned long nmemb, unsigned long size, void **ptr);
extern int findblkn(unsigned long nmemb);

extern void memory_reset(void);
extern void blkfree(void *ptr);

#endif /* MEMORY_H */
