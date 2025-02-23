#ifndef DEBUG_H
#define DEBUG_H
#ifdef NLOG

#define logmsg(fmt, msg)
#define crash()
#define assert(expr)

#else

#include <stdlib.h>
#include <stdio.h>

#define logmsg(fmt, msg) do{ \
	if((msg) == 0){ \
		printf((fmt)); \
	} \
	else{ \
		printf((fmt), (msg)); \
	} \
} \
while(0)

#define crash() do{ \
	abort(); \
} \
while(0)

#define assert(expr) do{ \
	if((expr) == 0){ \
		logmsg("%s\n", (#expr)); \
		logmsg("%s\n", __FILE__); \
		logmsg("%i\n", __LINE__); \
		crash(); \
	} \
} \
while(0)

#endif /* NDEBUG */
#endif /* DEBUG_H */
