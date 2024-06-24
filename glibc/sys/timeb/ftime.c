#include <sys/timeb.h>
#include <stdio.h>

int main(void)
{
	struct timeb timeb;

	/**
	 * This function is no longer provided by the GNU C library.
	 * Use clock_gettime(2) instead.
	 */
	ftime(&timeb);
	printf("%ld, %d, %d, %d\n", timeb.time, timeb.millitm, timeb.timezone,
		timeb.dstflag);

	return 0;
}
