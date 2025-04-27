#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "time_helpers.h"

int main(int argc, char **argv)
{
	struct timespec elapsed_from_boot;

	sys_clock_gettime(CLOCK_BOOTTIME, &elapsed_from_boot);
	printf("%ld - seconds elapsed from boot\n", elapsed_from_boot.tv_sec);

	clock_gettime(CLOCK_BOOTTIME, &elapsed_from_boot);
	printf("%ld - seconds elapsed from boot\n", elapsed_from_boot.tv_sec);

	return 0;
}
