#ifndef WINDOW_H
#define WINDOW_H

#include "./icons.h"

#define WNDWIDTH	40
#define WNDHEIGHT	20

extern struct icon window[WNDWIDTH * WNDHEIGHT];

extern int putwnd(void);

#endif /* WINDOW_H */
