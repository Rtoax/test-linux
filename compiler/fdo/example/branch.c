#include <stdio.h>
#include <stdlib.h>

#include "common.h"

unsigned long branch_A(unsigned long a);
unsigned long branch_B_7th(unsigned long a);
unsigned long branch_C_1st(unsigned long a);
unsigned long branch_D_6th(unsigned long a);
unsigned long branch_E_5th(unsigned long a);
unsigned long branch_F_4th(unsigned long a);
unsigned long branch_G_3rd(unsigned long a);
unsigned long branch_H_2nd(unsigned long a);


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
		else
			ret += branch_C_1st(i);
	}

	return ret;
}

unsigned long __noinline
branch_B_7th(unsigned long a)
{
	return a + 3;
}

unsigned long __noinline
branch_C_1st(unsigned long a)
{
	return a + 4;
}

unsigned long __noinline
branch_D_6th(unsigned long a)
{
	return a + 5;
}

unsigned long __noinline
branch_E_5th(unsigned long a)
{
	return a + 8;
}

unsigned long __noinline
branch_F_4th(unsigned long a)
{
	return a + 9;
}

unsigned long __noinline
branch_G_3rd(unsigned long a)
{
	return a + 11;
}

unsigned long __noinline
branch_H_2nd(unsigned long a)
{
	return a + 13;
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

