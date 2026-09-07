#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "vdso.h"

int main(int argc, char *argv[])
{
	struct timespec tp;

	while (1) {
		printf("Call clock_gettime from ");
#ifdef CUSTOM_VDSO
		vdso_clock_gettime(CLOCK_REALTIME, &tp);
		printf("custom");
#elif defined(KERNEL_VDSO64)
		clock_gettime(CLOCK_REALTIME, &tp);
		printf("kernel");
#endif
		printf(", timespec {tv_sec=%ld,tv_nsec=%ld}\n", tp.tv_sec,
		       tp.tv_nsec);
		sleep(3);
	}
}
