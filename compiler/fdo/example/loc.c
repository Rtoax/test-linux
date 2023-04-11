#include <stdio.h>
#include <stdlib.h>

#include "common.h"

/**
 * A --> B --> D
 * A --> C --> D
 */
unsigned long loc_A(unsigned long a);
unsigned long loc_B(unsigned long a);
unsigned long loc_C(unsigned long a);
unsigned long loc_D(unsigned long a);


unsigned long __noinline
loc_A(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++) {
		if (a % 100 == 0)
			ret += loc_B(i);
		else
			ret += loc_C(i);
	}

	return ret;
}

PAD_FN(a_pad_0);

unsigned long __noinline
loc_B(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++)
		ret += loc_D(i);

	return ret;
}

PAD_FN(a_pad_1);

unsigned long __noinline
loc_C(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++)
		ret += loc_D(i);

	return ret;
}

PAD_FN(a_pad_2);

unsigned long __noinline
loc_D(unsigned long a)
{
	return a++;
}

PAD_FN(a_pad_3);

unsigned long
test_add(void)
{
	return loc_A(20000);
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

