#include <stdio.h>
#include <unistd.h>

int fun1(void)
{
	union {
		unsigned long l;
		char c[8];
	} hello = {
		.c[0] = 'H',
		.c[1] = 'e',
		.c[2] = 'l',
		.c[3] = 'l',
		.c[4] = 'o',
		.c[5] = '\n',
	};

	char *s = (void *)&hello.l;
	write(1, s, 8);
	return 0;
}

void fun2(void)
{
	char s[8] = { "hello\n" };
	write(1, s, 8);
	return;
}

/**
 * TODO: Use asm()
 */

int main(void)
{
	fun1();
	return 0;
}
