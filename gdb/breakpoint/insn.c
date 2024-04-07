#include <stdio.h>

#if defined(__x86_64__) || defined(__i386__)
# define BREAKPOINT()	__asm__("int3")
#elif defined(__aarch64__)
# define BREAKPOINT()	__asm__("brk 0")
#endif

int func(void)
{
	BREAKPOINT();
}

int main(void)
{
	int i = 0;
	while (i < 6){
		printf("i : %d\n", i);
		BREAKPOINT();
		++i;
		func();
	}
}
