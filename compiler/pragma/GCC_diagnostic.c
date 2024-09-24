#include <stdio.h>


int main(void)
{
	int i;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wunused-variable"
#if __GNUC__ >= 11 && __GNUC_MINOR__ >= 1
/* Ignore read(2) overflow and write(2) overread compile warnings */
#pragma GCC diagnostic ignored "-Wstringop-overread"
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#endif
	printf("%d\n", i);
#pragma GCC diagnostic pop
	return 0;
}
