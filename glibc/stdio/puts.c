#include <stdio.h>

int main(void)
{
#if defined(__x86_64__)
	asm(
	"push   $0x44434241\n"
	"mov    %rsp,%rdi\n"
	"call   puts\n"
	"pop    %rsi\n");
#endif
	return 0;
}
