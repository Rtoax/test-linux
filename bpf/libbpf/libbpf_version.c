#include <stdio.h>
#include <bpf/libbpf.h>

int main(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "cflags")) {
			printf("-DLIBBPF_MAJOR_VERSION=%d -DLIBBPF_MINOR_VERSION=%d\n",
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
