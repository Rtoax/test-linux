#include <stdio.h>
#include <stdlib.h>

#include "common.h"

unsigned long __noinline loc_A(unsigned long a) { return a + 2; } PAD_FN(p_a);
unsigned long __noinline loc_B_hot(unsigned long a) { return a + 2; } PAD_FN(p_b);
unsigned long __noinline loc_C(unsigned long a) { return a + 3; } PAD_FN(p_c);
unsigned long __noinline loc_D(unsigned long a) { return a + 4; } PAD_FN(p_d);
unsigned long __noinline loc_E_hot(unsigned long a) { return a + 5; } PAD_FN(p_e);
unsigned long __noinline loc_F(unsigned long a) { return a + 6; } PAD_FN(p_f);
unsigned long __noinline loc_G(unsigned long a) { return a + 6; } PAD_FN(p_g);
unsigned long __noinline loc_H(unsigned long a) { return a + 6; } PAD_FN(p_h);
unsigned long __noinline loc_I(unsigned long a) { return a + 6; } PAD_FN(p_i);
unsigned long __noinline loc_J(unsigned long a) { return a + 6; } PAD_FN(p_j);
unsigned long __noinline loc_L(unsigned long a) { return a + 6; } PAD_FN(p_k);
unsigned long __noinline loc_M(unsigned long a) { return a + 6; } PAD_FN(p_l);
unsigned long __noinline loc_N(unsigned long a) { return a + 6; } PAD_FN(p_m);
unsigned long __noinline loc_O(unsigned long a) { return a + 6; } PAD_FN(p_n);
unsigned long __noinline loc_P_hot(unsigned long a) { return a + 6; } PAD_FN(p_1);

/**
 * A --> B
 * A --> E
 */
unsigned long __noinline
loc_caller(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++) {
		if (a % 3 == 0)
			ret += loc_B_hot(i);
		else if (a % 2 == 0)
			ret += loc_E_hot(i);
		else
			ret += loc_P_hot(i);
	}

	return ret;
}


unsigned long
test_add(unsigned long nloop)
{
	return loc_caller(nloop);
}

int main(int argc, char *argv[])
{
	unsigned long ret, nloop;

	if (argc >= 2)
		nloop = strtoul(argv[1], NULL, 10);
	else
		nloop = 20000000;

	start();
	ret = test_add(nloop);
	stop();

	printf("ret = %ld\n", ret);

	return 0;
}

