#include <stdio.h>


#if 1
asm(
	".pushsection .interp.my,\"a\"\n"
	"    .ascii \"/usr/bin/ld\\x00\"\n"
	".popsection"
);
#else
asm(
	".pushsection .interp,\"a\"\n"
	"        .incbin \"interp.section.txt\"\n"
	".popsection"
);
#endif

int main(void)
{
	printf("hello\n");
	return 0;
}

