#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define DEF_F(fname)	\
	unsigned long __noinline	\
	branch_f_##fname(unsigned long a) {	\
		return a + 1;	\
	}

DEF_F(9th)
DEF_F(8th)
DEF_F(7th)
DEF_F(6th)
DEF_F(5th)
DEF_F(4th)
DEF_F(3rd)
DEF_F(2nd)
DEF_F(1st)

unsigned long __noinline
branch_A(unsigned long a)
{
	unsigned long i, ret = 0;

	/**
	 * I deliberately put the number of function calls in reverse order
	 * of branching statements, and FDO will optimize the ordering of
	 * branching statements.
	 */
	for (i = 0; i < a; i++) {
		if (i % 23 == 1)
			ret += branch_f_9th(i);
		else if (i % 19 == 1)
			ret += branch_f_8th(i);
		else if (i % 17 == 1)
			ret += branch_f_7th(i);
		else if (i % 13 == 1)
			ret += branch_f_6th(i);
		else if (i % 11 == 1)
			ret += branch_f_5th(i);
		else if (i % 7 == 1)
			ret += branch_f_4th(i);
		else if (i % 5 == 1)
			ret += branch_f_3rd(i);
		else if (i % 3 == 1)
			ret += branch_f_2nd(i);
		else if (i % 2 == 1)
			ret += branch_f_1st(i);
		else
			ret += 1;
	}

	return ret;
}

unsigned long
test_branch(void)
{
	return branch_A(200000000);
}

int main()
{
	unsigned long ret;

	start();
	ret = test_branch();
	stop();

	printf("ret = %ld\n", ret);

	return 0;
}

