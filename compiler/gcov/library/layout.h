

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
#ifndef LAYOUT_FN_E
# error Undefined LAYOUT_FN_E
#endif
#ifndef LAYOUT_FN_F
# error Undefined LAYOUT_FN_F
#endif
#ifndef LAYOUT_FN_G
# error Undefined LAYOUT_FN_G
#endif
#ifndef LAYOUT_FN_H
# error Undefined LAYOUT_FN_H
#endif
#ifndef LAYOUT_FN_I
# error Undefined LAYOUT_FN_I
#endif
#ifndef LAYOUT_FN_J
# error Undefined LAYOUT_FN_J
#endif

/* like commit 3c9c8f2ab542("gcov/example: -O3 already optimize function
 * layout(todo)") said, this macro use to interfering compiler to not optimize
 * function layout.
 */
#if defined(HAVE_INTERFERING_COMPILER)
# define INTERFERING_COMPILER(a) ({	\
	unsigned long ____b = 0;	\
	if (unlikely(a == -1ULL)) {	\
		____b += LAYOUT_FN_A(a) + LAYOUT_FN_B(a) + LAYOUT_FN_C(a) +	\
			LAYOUT_FN_D(a) + LAYOUT_FN_E(a) + LAYOUT_FN_F(a) +	\
			LAYOUT_FN_G(a) + LAYOUT_FN_H(a) + LAYOUT_FN_I(a) +	\
			LAYOUT_FN_J(a);	\
	}	\
	____b;	\
})
#else
# define INTERFERING_COMPILER(a) (0)
#endif

unsigned long __noinline__ LAYOUT_FN_A(unsigned long);
unsigned long __noinline__ LAYOUT_FN_B(unsigned long);
unsigned long __noinline__ LAYOUT_FN_C(unsigned long);
unsigned long __noinline__ LAYOUT_FN_D(unsigned long);
unsigned long __noinline__ LAYOUT_FN_E(unsigned long);
unsigned long __noinline__ LAYOUT_FN_F(unsigned long);
unsigned long __noinline__ LAYOUT_FN_G(unsigned long);
unsigned long __noinline__ LAYOUT_FN_H(unsigned long);
unsigned long __noinline__ LAYOUT_FN_I(unsigned long);
unsigned long __noinline__ LAYOUT_FN_J(unsigned long);

/**
 *                    Layout   Opt Layout
 *       A              A          A
 *      / \             B          B
 * 100 /   \ 10         C          D
 *    /     \           D          F
 *   B       C          E          H
 *   |100    | 10       F          J
 *   D       E          G          C
 *   |100    | 10       H          E
 *   F       G          I          G
 *   |100    | 10       J          I
 *   H       I
 *    \     /
 * 100 \   / 10
 *      \ /
 *       J
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
	return LAYOUT_FN_D(a) + a + INTERFERING_COMPILER(a);
}

unsigned long __noinline__ LAYOUT_FN_C(unsigned long a)
{
	return LAYOUT_FN_E(a) + a + INTERFERING_COMPILER(a);
}

unsigned long __noinline__ LAYOUT_FN_D(unsigned long a)
{
	return LAYOUT_FN_F(a) + a + INTERFERING_COMPILER(a);
}

unsigned long __noinline__ LAYOUT_FN_E(unsigned long a)
{
	return LAYOUT_FN_G(a) + a + INTERFERING_COMPILER(a);
}

unsigned long __noinline__ LAYOUT_FN_F(unsigned long a)
{
	return LAYOUT_FN_H(a) + a + INTERFERING_COMPILER(a);
}

unsigned long __noinline__ LAYOUT_FN_G(unsigned long a)
{
	return LAYOUT_FN_I(a) + a + INTERFERING_COMPILER(a);
}

unsigned long __noinline__ LAYOUT_FN_H(unsigned long a)
{
	return LAYOUT_FN_J(a) + a + INTERFERING_COMPILER(a);
}

unsigned long __noinline__ LAYOUT_FN_I(unsigned long a)
{
	return LAYOUT_FN_J(a) + a + INTERFERING_COMPILER(a);
}

unsigned long __noinline__ LAYOUT_FN_J(unsigned long a)
{
	return a + a + INTERFERING_COMPILER(a);
}
