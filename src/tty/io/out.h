/* - terminal output functions - */

#ifndef OUT_H
#define OUT_H

#define OUT_ERR		0xff

/* all tty_game needs is a guarantee to put byte/s on
 * a terminal be it via stdout or manual hardware
 * writing. The user isnt expected to assume one or the
 * other. */

/* puts a byte in the terminal  and returns it, or it
 * returns OUT_ERR. */

extern char putb(char byte);

/* puts many bytes in the terminal returns amount of
 * bytes putted/printed, returns OUT_ERR on failure. */

extern char printb(char *str);

#endif /* OUT_H */
