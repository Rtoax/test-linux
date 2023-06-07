#include <stdio.h>

const char *cpu_arch(void)
{
	const char *arch = "Unknown";
#if defined(__x86_64__)
	arch = "x86_64";
#elif defined(__aarch64__)
	arch = "aarch64";
#endif
	return arch;
}

int main(void)
{
	printf("%s\n", cpu_arch());
	return 0;
}
