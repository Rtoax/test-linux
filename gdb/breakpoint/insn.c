#include <stdio.h>
#include <signal.h>

#if defined(__x86_64__) || defined(__i386__)
# define BREAKPOINT()	__asm__("int3")
#elif defined(__aarch64__)
# define BREAKPOINT()	__asm__("brk 0")
#endif

void sigtrap(int sig)
{
	printf("Get SIGTRAP.\n");
}

int func(void)
{
	BREAKPOINT();
}

int main(int argc, char *argv[])
{
	int i = 0;

	fprintf(stderr, "Usage: %s [sig]\n", argv[0]);

	if (argc > 1)
		signal(SIGTRAP, sigtrap);

	while (i < 6){
		printf("i : %d\n", i);
		BREAKPOINT();
		++i;
		func();
	}
}
