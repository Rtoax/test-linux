#include <stdio.h>
#include <stdint.h>
#include <cpuid.h>

int main(int argc, char *argv[])
{
	uint32_t eax, ebx, ecx, edx;
	int ret = 0;

	eax = ebx = ecx = edx = 0;
	ret = __get_cpuid(1, &eax, &ebx, &ecx, &edx);
	if (ret == 0) {
		fprintf(stderr, "__get_cpuid() error.\n");
		ret = 1;
	}

	printf("%#08x %#08x %#08x %#08x \n", eax, ebx, ecx, edx);

done:
	return ret;
}

