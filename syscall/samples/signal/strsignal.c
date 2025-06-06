#include <stdio.h>
#include <string.h>
#include <signal.h>

int main(void)
{
	int i, flags[NSIG] = {0};

#define NR_SIG(nr) do {	\
	printf("%-16s (%2d) : %-8s %s\n", #nr, nr, sigabbrev_np(nr), strsignal(nr));	\
	flags[nr] = 1;	\
	} while (0);
#include "sig.h"
#undef NR_SIG

	/**
	 * - linux kernel SIGRTMIN is 32.
	 * - POSIX SIGRTMIN is 34 or 35, see signal(7)
	 *   - glibc is 34: sysdeps/unix/sysv/linux/internal-signals.h:#define RESERVED_SIGRT  2
	 *   - musl-libc is 35: https://git.musl-libc.org/cgit/musl/tree/src/signal/sigrtmin.c
	 */
	for (i = 0; i < NSIG; i++) {
		if (flags[i])
			continue;
		printf("%-16s (%2d) : %s %s\n", "", i, sigabbrev_np(i), strsignal(i));
	}

	return 0;
}
