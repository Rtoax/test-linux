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
#else
# warning Unkown arch
	name = "unknown-arch";
#endif

	arch = seccomp_arch_resolve_name(name);

	printf("arch %x\n", arch);

	return 0;
}
