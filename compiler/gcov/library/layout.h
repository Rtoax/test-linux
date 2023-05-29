

#ifndef LAYOUT_FN_TEST
# error Undefined LAYOUT_FN_TEST
#endif
#ifndef LAYOUT_FN_A
# error Undefined LAYOUT_FN_A
#endif
#ifndef LAYOUT_FN_B
# error Undefined LAYOUT_FN_B
#endif
#ifndef LAYOUT_FN_C
# error Undefined LAYOUT_FN_C
#endif
#ifndef LAYOUT_FN_D
# error Undefined LAYOUT_FN_D
#endif

unsigned long __noinline__ LAYOUT_FN_A(unsigned long);
unsigned long __noinline__ LAYOUT_FN_B(unsigned long);
unsigned long __noinline__ LAYOUT_FN_C(unsigned long);
unsigned long __noinline__ LAYOUT_FN_D(unsigned long);

/**
 *                    Layout   Opt Layout
 *       A              A          A
 *      / \             B          B
 * 100 /   \ 10         C          D
 *    /     \           D          C
 *   B       C
 *    \     /
 * 100 \   / 10
 *      \ /
 *       D
 */

unsigned long LAYOUT_FN_TEST(void)
{
	unsigned long ret;

	srand((int)time(0));

	return LAYOUT_FN_A(rand() % 10000000);
}

unsigned long __noinline__ LAYOUT_FN_A(unsigned long a)
{
	unsigned long ret = 0;
	int i;
	for (i = 0; i < 100; i++) {
		if (i % 10 == 0)
			ret += LAYOUT_FN_B(i);
		else
			ret += LAYOUT_FN_B(i);
	}
	return ret;
}

unsigned long __noinline__ LAYOUT_FN_B(unsigned long a)
{
	return LAYOUT_FN_D(a) + a;
}

unsigned long __noinline__ LAYOUT_FN_C(unsigned long a)
{
	return LAYOUT_FN_D(a) + a;
}

unsigned long __noinline__ LAYOUT_FN_D(unsigned long a)
{
	return a * 2;
}
