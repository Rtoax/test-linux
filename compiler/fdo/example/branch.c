#include <stdio.h>
#include <stdlib.h>

#include "common.h"

unsigned long f_A(unsigned long a);
unsigned long f_B(unsigned long a);
unsigned long f_C(unsigned long a);
unsigned long f_D(unsigned long a);

#define NR_MIN	10000
#define NR_MAX	100000

unsigned long __noinline
f_A(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MAX; i+=2) {
		/* this branch never run */
		if (i % 2 == 1)
			a += f_B(i);
		/* this branch never run */
		else if (i % 3 == 1)
			a += f_B(i) + f_C(i);
		/* this branch will run */
		else if (i % 2 == 0)
			a += f_C(i);
	}

	return a;
}

unsigned long __noinline
f_B(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MIN; i++)
		a += f_D(i);

	return a;
}

unsigned long __noinline
f_C(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MIN; i++)
		a += f_D(i);

	return a;
}

unsigned long __noinline
f_D(unsigned long a)
{
	return a++;
}

unsigned long
test_branch(void)
{
	return f_A(1);
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

