
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


DEFINE_FN1(1st)
DEFINE_FN1(2nd)
DEFINE_FN1(3rd)
DEFINE_FN1(4th)
DEFINE_FN1(5th)
DEFINE_FN1(6th)
DEFINE_FN1(7th)

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
		if (i % 400 == 1)
			ret += CALLED_FN1(7th, i);
		else if (i % 300 == 2)
			ret += CALLED_FN1(6th, i);
		else if (i % 200 == 3)
			ret += CALLED_FN1(5th, i);
		else if (i % 100 == 4)
			ret += CALLED_FN1(4th, i);
		else if (i % 50 == 5)
			ret += CALLED_FN1(3rd, i);
		else if (i % 10 == 6)
			ret += CALLED_FN1(2nd, i);
		else if (i % 2 == 1)
			ret += CALLED_FN1(1st, i);
		else
			ret += 1;
	}

	return ret;
}
