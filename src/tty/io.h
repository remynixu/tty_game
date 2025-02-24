#ifndef IO_H
#define IO_H

#define IO_ERR		-1

extern int putb(char c);
extern int printb(char *str);

extern char pollb(void);

#endif /* IO_H */
