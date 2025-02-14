#ifndef GFXINFO_CONFIG_H
#define GFXINFO_CONFIG_H

#include "../../../config.h"

#if COLORMODE		COLORMODE_NONE

#define __NOCLR

#elif COLORMODE		COLORMODE_BASIC

#define __BASICCLR

#else

#error "you should properly configure coloring first.\n"

#endif /* COLORMODE */

#endif /* GFXINFO_CONFIG_H */
