#ifndef OUT_H
#define OUT_H

#define OUT_ERR		-1

/*
 * @brief - putb()
 * - put a byte on terminal.
 * @return
 * - success: int representation of argument.
 * - fail: OUT_ERR
 */
extern int putb(char b);

/*
 * @brief - printb()
 * - puts an array of bytes to screen.
 * @return
 * - success: number of bytes printed.
 * - fail: OUT_ERR
 */
extern int printb(char *str);

#endif /* OUT_H */
