/* - terminal input functions */

#ifndef IN_H
#define IN_H

#define POLL_ERR	0xff

/* minimize guarantees for minimized disappointment, for
 * the user ;) */

/* we need a way to get input in the form of a simple
 * interface.
 *
 * returns byte recieved from any input source
 * implementation defined, POLL_ERR on failure. */

extern char pollb(void);

/* for multibyte polling.
 *
 * returns 0, POLL_ERR on atleast one failed poll. */

extern char pollnb(char count);

#endif /* IN_H */
