#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>

int main(int argc, char **argv)
{
	unsigned long i = 0;

	if (argc < 2) {
		printf("Usage: a.out [vsyscall|vdso|syscall]\n");
		exit(1);
	}

	if (!strcmp(argv[1], "vsyscall")) {
		/**
		 * Addr is `$ sudo cat /proc/[PID]/maps| grep "vsyscall"`
		 * 0xffffffffff600000UL
		 *
		 * TODO: segv fault here
		 */
		time_t (*f)(time_t *) = (time_t (*)(time_t *))0xffffffffff600000UL;
		for (i = 0; i < 1000000; ++i)
			f(NULL);
	} else if (!strcmp(argv[1], "vdso")) {
		for (i = 0; i < 1000000;++i)
			time(NULL);
	} else if (!strcmp(argv[1], "syscall")) {
		for (i = 0; i < 1000000; ++i)
			syscall(SYS_time, NULL);
	}

	return 0;
}
