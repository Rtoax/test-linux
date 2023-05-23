#include "likely.h"
#include "inline.h"
#include "unused.h"

#define DEFINE_FUNC(fname)	\
	unsigned long __noinline f_##fname(unsigned long a) { return a + 1; }

DEFINE_FUNC(1st)
DEFINE_FUNC(2nd)
DEFINE_FUNC(3rd)
DEFINE_FUNC(4th)
DEFINE_FUNC(5th)
DEFINE_FUNC(6th)
DEFINE_FUNC(7th)

unsigned long __noinline branches(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++) {
		if (unlikely(i % 400 == 1))
			ret += f_7th(i);
		else if (unlikely(i % 300 == 2))
			ret += f_6th(i);
		else if (i % 200 == 3)
			ret += f_5th(i);
		else if (i % 100 == 4)
			ret += f_4th(i);
		else if (likely(i % 50 == 5))
			ret += f_3rd(i);
		else if (i % 10 == 6)
			ret += f_2nd(i);
		else if (likely(i % 2 == 1))
			ret += f_1st(i);
		else
			ret += 1;
	}

	return ret;
}

int main(void)
{
	unsigned long __unused ret = branches(10000);
	return 0;
}
