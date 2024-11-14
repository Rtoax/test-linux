#include <stdio.h>

int main(void)
{
#define P(v) printf("%-16s : %d\n", #v, v);
	P(__ATOMIC_RELAXED);
	P(__ATOMIC_CONSUME);
	P(__ATOMIC_ACQUIRE);
	P(__ATOMIC_RELEASE);
	P(__ATOMIC_ACQ_REL);
	P(__ATOMIC_SEQ_CST);
#undef P
	return 0;
}
