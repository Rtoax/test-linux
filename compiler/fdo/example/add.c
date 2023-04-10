#include <stdio.h>
#include <stdlib.h>

#include "common.h"

/**
 * A --> B --> D
 * A --> C --> D
 */
unsigned long A(unsigned long a);
unsigned long B(unsigned long a);
unsigned long C(unsigned long a);
unsigned long D(unsigned long a);

#define NR_MIN	1000
#define NR_MAX	100000

unsigned long __noinline __opt_O0
A(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MIN; i++)
		a += B(i);

	for (i = 0; i < NR_MAX; i++)
		a += C(i);

	return a;
}

unsigned long __noinline __opt_O0
B(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MIN; i++)
		a += D(i);

	return a;
}

unsigned long __noinline __opt_O0
C(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MAX; i++)
		a += D(i);

	return a;
}

unsigned long __noinline __opt_O0
D(unsigned long a)
{
	return a++;
}

unsigned long
test_add(void)
{
	return A(1);
}

int main()
{
	unsigned long ret;

	start();
	ret = test_add();
	stop();

	printf("ret = %ld\n", ret);

	return 0;
}

