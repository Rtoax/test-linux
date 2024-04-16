#include <stdio.h>


int main(void)
{
	int i;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wunused-variable"
	printf("%d\n", i);
#pragma GCC diagnostic pop
	return 0;
}
