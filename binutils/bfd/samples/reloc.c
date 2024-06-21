#include <bfd.h>
#include <stdio.h>

int main(void)
{
#if defined(__aarch64__)
	printf("%d\n", BFD_RELOC_AARCH64_JUMP26);
#elif defined(__x86_64__)
	printf("%d\n", BFD_RELOC_X86_64_GOT32);
#endif
	return 0;
}
