/**
 * https://www.redhat.com/en/blog/hardening-elf-binaries-using-relocation-read-only-relro
 */
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	size_t *p;

	if (argc < 2) {
		fprintf(stderr, "%s [addr]\n", argv[0]);
		exit(1);
	}

	p = (size_t *)strtol(argv[1], NULL, 16);

	p[0] = 0xDEADBEEF;

	printf("RELRO: %p\n", p);

	return 0;
}

