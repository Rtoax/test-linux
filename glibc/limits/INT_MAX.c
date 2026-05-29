#include <stdio.h>
#include <limits.h>

int main(void)
{
#define Pd(v) printf("%-16s = %d\n", #v, v)
#define Pld(v) printf("%-16s = %ld\n", #v, v)
#define Plld(v) printf("%-16s = %lld\n", #v, v)
	Pd(INT_MAX);
	Pld(LONG_MAX);
	Plld(LLONG_MAX);
#undef Pd
#undef Pld
#undef Plld
	return 0;
}
