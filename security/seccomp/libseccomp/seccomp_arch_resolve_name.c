#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <seccomp.h>
#include <linux/seccomp.h>


int main(void)
{
	uint32_t arch;
	char *name;

#if defined(__sw_64__)
	name = "sw_64";
#elif defined(__x86_64__)
	name = "x86_64";
#elif defined(__aarch64__)
	name = "aarch64";
#else
# warning Unkown arch
	name = "unknown-arch";
#endif

	arch = seccomp_arch_resolve_name(name);

	printf("arch %x\n", arch);

	return 0;
}
