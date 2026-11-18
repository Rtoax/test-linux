#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

#ifndef CPU_ARCH
#error "Not defined CPU_ARCH, you need to include arch.mk in Makefile"
#endif

int main(void)
{
	struct utsname name;
	uname(&name);

	if (strcmp(name.machine, CPU_ARCH)) {
		exit(EXIT_FAILURE);
	}

#define CHK_IS(s_arch, macro_arch)                  \
	do {                                        \
		if (strcmp(name.machine, s_arch)) { \
			if (macro_arch != 1) {      \
				exit(EXIT_FAILURE); \
			}                           \
		}                                   \
	} while (0)

#ifdef __x86_64__
	CHK_IS("x86_64", IS_X86_64);
#elif defined(__aarch64__)
	CHK_IS("aarch64", IS_AARCH64);
#else
#error "add more cpu arch support"
#endif

	return 0;
}
