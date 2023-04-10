#include <stdio.h>
#include <stdlib.h>

#include "common.h"

unsigned long f_A(unsigned long a);
unsigned long f_B(unsigned long a);
unsigned long f_C(unsigned long a);
unsigned long f_D(unsigned long a);


unsigned long __noinline
f_A(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++) {
		/* this branch never run */
		if (i % 319 == 1)
			ret += f_B(i);
		/* this branch never run */
		else if (i % 217 == 1)
			ret += f_B(i) + f_C(i);
		/* this branch will run */
		else if (i % 2 == 0)
			ret += f_C(i);
	}

	return ret;
}

unsigned long __noinline
f_B(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++)
		ret += f_D(i);

	return ret;
}

unsigned long __noinline
f_C(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++)
		ret += f_D(i);

	return ret;
}

unsigned long __noinline
f_D(unsigned long a)
{
	return a++;
}

unsigned long
test_branch(void)
{
	return f_A(20000);
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

