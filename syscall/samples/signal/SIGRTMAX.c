#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

/**
 * - linux kernel SIGRTMIN is 32.
 * - POSIX SIGRTMIN is 34 or 35, see signal(7)
 *   - glibc is 32: sysdeps/unix/sysv/linux/internal-signals.h:#define RESERVED_SIGRT  2
 *   - musl-libc is 35: https://git.musl-libc.org/cgit/musl/tree/src/signal/sigrtmin.c
 */
#define LIBC_SIGRTMIN		(__libc_current_sigrtmin())
#define LIBC_SIGRTMAX		(__libc_current_sigrtmax())

/* glibc: sysdeps/unix/sysv/linux/internal-signals.h */
#define SIGCANCEL	32
#define SIGTIMER	SIGCANCEL
#define SIGSETXID	33

void handler(int sig, siginfo_t *si, void *context)
{
	printf("Received signal %d with value %d\n", sig, si->si_value.sival_int);
}

int main(int argc, char *argv[])
{
	struct sigaction sa;
	sigset_t mask;
	int rtoff = 20;

	printf("SIGRTMIN = %d, LIBC_SIGRTMIN = %d\n", SIGRTMIN, LIBC_SIGRTMIN);
	printf("SIGRTMAX = %d, LIBC_SIGRTMAX = %d\n", SIGRTMAX, LIBC_SIGRTMAX);
#ifdef CONST_SIGRTMIN
	printf("CONST_SIGRTMIN = %d\n", CONST_SIGRTMIN);
#endif
#ifdef CONST_SIGRTMAX
	printf("CONST_SIGRTMAX = %d\n", CONST_SIGRTMAX);
#endif

	/* Set up signal handler */
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN + rtoff, &sa, NULL);

	/* Block the signal temporarily */
	sigemptyset(&mask);
	sigaddset(&mask, SIGRTMIN + rtoff);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	/* Send a real-time signal with additional data */
	union sigval sv;
	sv.sival_int = 520;
	sigqueue(getpid(), SIGRTMIN + rtoff, sv);

	/* Unblock the signal */
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	/* Wait for signal to be handled */
	printf("Press ctrl-C to end.\n");
	pause();

	return 0;
}
