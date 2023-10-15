#include <stdio.h>


#define atomic_forced_read(x) ({ \
	__typeof(x) __x; \
	__asm("" : "=r" (__x) : "0" (x)); __x; \
})

int main(void)
{
	int a = 10;
	printf("%d\n", atomic_forced_read(a));
	return 0;
}
