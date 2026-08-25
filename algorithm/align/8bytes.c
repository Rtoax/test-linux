#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	uint64_t val = 19, rslt;

	if (argc > 1) {
		val = strtoul(argv[1], NULL, 10);
	}

	rslt = (val + 7) & ~7ULL;

	printf("%ld : %ld (0x%lx)\n", val, rslt, rslt);

	return 0;
}
