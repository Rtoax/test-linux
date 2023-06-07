#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

const char *cpu_arch(void)
{
	const char *arch = "Unknown";

#if defined(__x86_64__)
	arch = "x86_64";
#elif defined(__aarch64__)
	arch = "aarch64";
#else
	static struct utsname name;
	if (uname(&name) == -1) {
		fprintf(stderr, "cannot get system name");
	} else {
		arch = name.machine;
	}
#endif
	return arch;
}

int main(void)
{
	printf("%s\n", cpu_arch());
	return 0;
}
