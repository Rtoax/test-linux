#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define DEF_F(fname)	\
	unsigned long __noinline	\
	branch_##fname(unsigned long a) {	\
		return a + 1;	\
	}

DEF_F(B_7th)
DEF_F(D_6th)
DEF_F(E_5th)
DEF_F(F_4th)
DEF_F(G_3rd)
DEF_F(H_2nd)
DEF_F(C_1st)

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
		if (i % 400 == 1)
			ret += branch_B_7th(i);
		else if (i % 300 == 2)
			ret += branch_D_6th(i);
		else if (i % 200 == 3)
			ret += branch_E_5th(i);
		else if (i % 100 == 4)
			ret += branch_F_4th(i);
		else if (i % 50 == 5)
			ret += branch_G_3rd(i);
		else if (i % 10 == 6)
			ret += branch_H_2nd(i);
		else if (i % 2 == 1)
			ret += branch_C_1st(i);
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

