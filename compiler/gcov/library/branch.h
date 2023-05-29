
#ifndef LIB_BRANCH_FN
# error Undefined LIB_BRANCH_FN
#endif

#ifdef COMPILE_LIB
# define DEFINE_FN1(fname)	\
	unsigned long __attribute__((noinline)) lib_fn1_branch_##fname(unsigned long a) {	\
		return a + 3;	\
	}
# define CALLED_FN1(fname, i) lib_fn1_branch_##fname(i)
#elif defined(COMPILE_TEST)
# define DEFINE_FN1(fname)	\
	unsigned long __attribute__((noinline)) test_fn1_branch_##fname(unsigned long a) {	\
		return a + 3;	\
	}
# define CALLED_FN1(fname, i) test_fn1_branch_##fname(i)
#else
# error Must define COMPILE_LIB or COMPILE_TEST
#endif


DEFINE_FN1(1)
DEFINE_FN1(2)
DEFINE_FN1(3)
DEFINE_FN1(4)
DEFINE_FN1(5)
DEFINE_FN1(6)
DEFINE_FN1(7)
DEFINE_FN1(8)
DEFINE_FN1(9)
DEFINE_FN1(10)
DEFINE_FN1(11)

unsigned long __noinline__
LIB_BRANCH_FN(unsigned long a)
{
	unsigned long i, ret = 0;

	/**
	 * I deliberately put the number of function calls in reverse order
	 * of branching statements, and FDO will optimize the ordering of
	 * branching statements.
	 */
	for (i = 0; i < a; i++) {
		if (i % 31 == 1)
			ret += CALLED_FN1(11, i);
		else if (i % 29 == 1)
			ret += CALLED_FN1(10, i);
		else if (i % 23 == 1)
			ret += CALLED_FN1(9, i);
		else if (i % 19 == 1)
			ret += CALLED_FN1(8, i);
		else if (i % 17 == 1)
			ret += CALLED_FN1(7, i);
		else if (i % 13 == 1)
			ret += CALLED_FN1(6, i);
		else if (i % 11 == 1)
			ret += CALLED_FN1(5, i);
		else if (i % 7 == 1)
			ret += CALLED_FN1(4, i);
		else if (i % 5 == 1)
			ret += CALLED_FN1(3, i);
		else if (i % 3 == 1)
			ret += CALLED_FN1(2, i);
		else if (i % 2 == 1)
			ret += CALLED_FN1(1, i);
		else
			ret += 1;
	}

	return ret;
}
