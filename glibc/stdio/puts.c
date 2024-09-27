#include <stdio.h>

int main(void)
{
#if defined(__x86_64__)
	__asm__("push   $0x44434241\n"
		"mov    %rsp,%rdi\n"
		"call   puts\n"
		"pop    %rsi\n");
#elif defined(__i386__)
#endif
	char s1[] = {"ABCD"};
	puts(s1);
	puts("ABCD");
	return 0;
}
