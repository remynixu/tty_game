#ifndef IN_H
#define IN_H

#define IN_ERR		-1

/*
 * @brief - pollb()
 * - gets input from the user, the rest is
 *   implementation-defined.
 * @return
 * - success: polled byte
 * - fail: IN_ERR
 */
extern unsigned char pollb(void);

#endif /* IN_H */
