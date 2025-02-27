#ifndef ASSERT_H
#define ASSERT_H
#ifndef NASSERT

#define crash(){ \
	char *brk = 0; \
	*brk = 0; \
}

#define assert(expr){ \
	if(!(expr)) \
		crash(); \
}

#else

#define crash()
#define assert(expr)

#endif /* NASSERT */
#endif /* ASSERT_H */
