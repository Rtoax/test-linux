#include <stdio.h>
#include <stdlib.h>

#include "common.h"

unsigned long f_A(unsigned long a);
unsigned long f_B(unsigned long a);
unsigned long f_C(unsigned long a);
unsigned long f_D(unsigned long a);
unsigned long f_E(unsigned long a);
unsigned long f_F(unsigned long a);


unsigned long __noinline
f_A(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++) {
		if (i % 400 == 1)
			ret += f_B(i);
		else if (i % 300 == 2)
			ret += f_D(i);
		else if (i % 200 == 3)
			ret += f_E(i);
		else if (i % 100 == 4)
			ret += f_F(i);
		else if (i % 2 == 0)
			ret += f_C(i);
	}

	return ret;
}

unsigned long __noinline
f_B(unsigned long a)
{
	return a + 3;
}

unsigned long __noinline
f_C(unsigned long a)
{
	return a + 4;
}

unsigned long __noinline
f_D(unsigned long a)
{
	return a + 5;
}

unsigned long __noinline
f_E(unsigned long a)
{
	return a + 8;
}

unsigned long __noinline
f_F(unsigned long a)
{
	return a + 9;
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

