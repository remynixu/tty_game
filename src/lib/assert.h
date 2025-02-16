#ifndef ASSERT_H
#define ASSERT_H

/* these are just quick, hacked up test helpers. */

#define __assert(expr) \
	if((expr) == 0){ \
		char *brk; \
		brk[9] = 8; \
	}

#endif /* ASSERT_H */
