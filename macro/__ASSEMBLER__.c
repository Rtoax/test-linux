#include <stdio.h>

int main(void)
{
#ifdef __ASSEMBLER__
	/* This macro is defned with value 1 when preprocessing assembly language. */
	printf("__ASSEMBLER__ %d\n", __ASSEMBLER__);
#endif
	return 0;
}
