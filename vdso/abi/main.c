#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "vdso.h"

int main(int argc, char *argv[])
{
	struct timespec tp;

	while (1) {
#ifdef CUSTOM_VDSO
		vdso_clock_gettime(CLOCK_REALTIME, &tp);
#elif defined(KERNEL_VDSO64)
		clock_gettime(CLOCK_REALTIME, &tp);
		printf("Call clock_gettime from kernel vdso64.so.\n");
#endif
		sleep(3);
	}
}
