#include <stdio.h>
#include "alt.h"


void __attribute__((constructor)) do_alt(void)
{
	unsigned long start = __alt_instructions;
}

int main(void)
{
	return 0;
}
