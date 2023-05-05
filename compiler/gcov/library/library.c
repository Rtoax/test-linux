#include <stdio.h>

#include "library.h"


#define FN1(fname)	\
unsigned long __attribute__((noinline)) fn1_##fname(unsigned long a) {	\
	return a + 3;	\
}

FN1(branch_1st)
FN1(branch_2nd)
FN1(branch_3rd)
FN1(branch_4th)
FN1(branch_5th)
FN1(branch_6th)
FN1(branch_7th)

unsigned long __noinline__
lib_branch_f1(unsigned long a)
{
	unsigned long i, ret = 0;

	/**
	 * I deliberately put the number of function calls in reverse order
	 * of branching statements, and FDO will optimize the ordering of
	 * branching statements.
	 */
	for (i = 0; i < a; i++) {
		if (i % 400 == 1)
			ret += fn1_branch_7th(i);
		else if (i % 300 == 2)
			ret += fn1_branch_6th(i);
		else if (i % 200 == 3)
			ret += fn1_branch_5th(i);
		else if (i % 100 == 4)
			ret += fn1_branch_4th(i);
		else if (i % 50 == 5)
			ret += fn1_branch_3rd(i);
		else if (i % 10 == 6)
			ret += fn1_branch_2nd(i);
		else
			ret += fn1_branch_1st(i);
	}

	return ret;
}


int lib_f1(void)
{
	lib_branch_f1(100000);

	return 0;
}

