#include <stdio.h>
#include <stdlib.h>

#include "common.h"

/**
 * A --> B --> D
 * A --> C --> D
 */
unsigned long FN(A)(unsigned long a);
unsigned long FN(B)(unsigned long a);
unsigned long FN(C)(unsigned long a);
unsigned long FN(D)(unsigned long a);

#define NR_MIN	1000
#define NR_MAX	100000

unsigned long __noinline
FN(A)(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MIN; i++)
		a += CALL(B)(i);

	for (i = 0; i < NR_MAX; i++)
		a += CALL(C)(i);

	return a;
}

DEFINE_FN_PAD(_p1);
DEFINE_FN_PAD(_p2);
DEFINE_FN_PAD(_p3);
DEFINE_FN_PAD(_p4);
DEFINE_FN_PAD(_p5);
DEFINE_FN_PAD(_p6);
DEFINE_FN_PAD(_p7);
DEFINE_FN_PAD(_p8);
DEFINE_FN_PAD(_p9);
DEFINE_FN_PAD(_p10);
DEFINE_FN_PAD(_p11);
DEFINE_FN_PAD(_p12);

unsigned long __noinline
FN(B)(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MIN; i++)
		a += CALL(D)(i);

	return a;
}

DEFINE_FN_PAD(_1);
DEFINE_FN_PAD(_2);
DEFINE_FN_PAD(_3);
DEFINE_FN_PAD(_4);
DEFINE_FN_PAD(_5);
DEFINE_FN_PAD(_6);
DEFINE_FN_PAD(_7);
DEFINE_FN_PAD(_8);
DEFINE_FN_PAD(_9);
DEFINE_FN_PAD(_10);
DEFINE_FN_PAD(_11);
DEFINE_FN_PAD(_12);

unsigned long __noinline
FN(C)(unsigned long a)
{
	unsigned long i;

	for (i = 0; i < NR_MAX; i++)
		a += CALL(D)(i);

	return a;
}

DEFINE_FN_PAD(p_1);
DEFINE_FN_PAD(p_2);
DEFINE_FN_PAD(p_3);
DEFINE_FN_PAD(p_4);
DEFINE_FN_PAD(p_5);
DEFINE_FN_PAD(p_6);
DEFINE_FN_PAD(p_7);
DEFINE_FN_PAD(p_8);
DEFINE_FN_PAD(p_9);
DEFINE_FN_PAD(p_10);
DEFINE_FN_PAD(p_11);
DEFINE_FN_PAD(p_12);

unsigned long __noinline
FN(D)(unsigned long a)
{
	return a++;
}

unsigned long
FN(test_add)(void)
{
	return CALL(A)(1);
}
