#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "vdso.h"

int main(int argc, char *argv[])
{
	while (1) {
#ifdef CUSTOM_VDSO
		my_clock_gettime();
#elif defined(KERNEL_VDSO64)
		struct timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		printf("Call clock_gettime from kernel vdso64.so.\n");
#endif
		sleep(3);
	}
}
