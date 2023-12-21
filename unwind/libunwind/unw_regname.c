#include <stdio.h>
#include <libunwind.h>


int main(void)
{
	int i;
	for (i = 0; i < 18; i++) {
		printf("i=%4d, %s\n", i, unw_regname(i));
	}
	return 0;
}
