#ifndef IO_H
#define IO_H

/*
 * This library is made for easier-to-edit input and output functionality! >_<
 *
 * - remynixu
 */

/*
 * Constants!
 */

#include "presets.h"



/* TODO: We intend to make it so that the user can make files via memory, hence
 *       why we are still waiting for block.h to finish... */
/*
 * Instead of "FILE"s, we work with ports! Only because we're quirky... ^-^
 */

typedef struct{
	size_t id;
}PORT;

/* TODO */
/*
 * The default ports, similar to their stdio.h counterparts!
 */

#define port_in		0
#define port_out	1
#define port_err	2

/* TODO */
/*
 * Here are the I/O functions! Similar to their stdio.h counterparts...
 */



#endif /* IO_H */
