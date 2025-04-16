#include <stdio.h>
#include <bpf/libbpf.h>

int main(int argc, char *argv[])
{
/**
 * libbpf commit 8ade99a6f84d ("libbpf: Make libbpf_version.h non-auto-generated")
 * v0.6.0 add macro LIBBPF_MAJOR_VERSION and LIBBPF_MINOR_VERSION in libbpf_version.h
 */
#ifndef LIBBPF_MAJOR_VERSION
#define LIBBPF_MAJOR_VERSION LIB_LIBBPF_MAJOR_VERSION
#endif
#ifndef LIBBPF_MINOR_VERSION
#define LIBBPF_MINOR_VERSION LIB_LIBBPF_MINOR_VERSION
#endif

#if (LIBBPF_MAJOR_VERSION != LIB_LIBBPF_MAJOR_VERSION) || (LIBBPF_MINOR_VERSION != LIB_LIBBPF_MINOR_VERSION)
#error "libbpf version fatal, 'ldconfig -p | grep libbpf' != /usr/include/bpf/libbpf_version.h"
#endif
	int i;
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "cflags")) {
			printf("-DLIBBPF_MAJOR_VERSION=%d -DLIBBPF_MINOR_VERSION=%d\n",
				LIBBPF_MAJOR_VERSION, LIBBPF_MINOR_VERSION);
			return 0;
		}
		if (!strcmp(argv[i], "env")) {
			printf("LIBBPF_MAJOR_VERSION=%d LIBBPF_MINOR_VERSION=%d\n",
				LIBBPF_MAJOR_VERSION, LIBBPF_MINOR_VERSION);
			return 0;
		}
	}
	if (i == argc) {
		printf("LIBBPF_MAJOR_VERSION = %d\n", LIBBPF_MAJOR_VERSION);
		printf("LIBBPF_MINOR_VERSION = %d\n", LIBBPF_MINOR_VERSION);
	}
	return 0;
}
