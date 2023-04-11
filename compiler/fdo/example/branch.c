#include <stdio.h>
#include <stdlib.h>

#include "common.h"

unsigned long f_A(unsigned long a);
unsigned long f_B_7th(unsigned long a);
unsigned long f_C_1st(unsigned long a);
unsigned long f_D_6th(unsigned long a);
unsigned long f_E_5th(unsigned long a);
unsigned long f_F_4th(unsigned long a);
unsigned long f_G_3rd(unsigned long a);
unsigned long f_H_2nd(unsigned long a);


unsigned long __noinline
f_A(unsigned long a)
{
	unsigned long i, ret = 0;

	/**
	 * I deliberately put the number of function calls in reverse order
	 * of branching statements, and FDO will optimize the ordering of
	 * branching statements.
	 */
	for (i = 0; i < a; i++) {
		if (i % 400 == 1)
			ret += f_B_7th(i);
		else if (i % 300 == 2)
			ret += f_D_6th(i);
		else if (i % 200 == 3)
			ret += f_E_5th(i);
		else if (i % 100 == 4)
			ret += f_F_4th(i);
		else if (i % 50 == 5)
			ret += f_G_3rd(i);
		else if (i % 10 == 6)
			ret += f_H_2nd(i);
		else
			ret += f_C_1st(i);
	}

	return ret;
}

unsigned long __noinline
f_B_7th(unsigned long a)
{
	return a + 3;
}

unsigned long __noinline
f_C_1st(unsigned long a)
{
	return a + 4;
}

unsigned long __noinline
f_D_6th(unsigned long a)
{
	return a + 5;
}

unsigned long __noinline
f_E_5th(unsigned long a)
{
	return a + 8;
}

unsigned long __noinline
f_F_4th(unsigned long a)
{
	return a + 9;
}

unsigned long __noinline
f_G_3rd(unsigned long a)
{
	return a + 11;
}

unsigned long __noinline
f_H_2nd(unsigned long a)
{
	return a + 13;
}

unsigned long
test_branch(void)
{
	return f_A(200000000);
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

