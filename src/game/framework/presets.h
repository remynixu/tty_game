#ifndef PRESETS_H
#define PRESETS_H



/*
 * Presets!!!
 */

#define BIT_SYSTEM	32



/*
 * Effects of presets (>o<)
 */

#if BIT_SYSTEM == 8
#warning "lol what the fuck are you coding this on? XD"
typedef unsigned short size_t;
#elif BIT_SYSTEM == 16
typedef unsigned int size_t;
#elif BIT_SYSTEM == 32
typedef unsigned long size_t;
#elif BIT_SYSTEM == 64
typedef unsigned long long size_t;
#endif /* BIT_SYSTEM */

typedef unsigned char uint8_t;



/*
 * Constants, I guess...
 */

#ifndef NULL
#define NULL	((void *)0)
#endif /* NULL */



#endif /* PRESETS_H */
