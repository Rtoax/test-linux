#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#define LIBC_SIGRTMIN        (__libc_current_sigrtmin())
#define LIBC_SIGRTMAX        (__libc_current_sigrtmax())


int main(int argc, char *argv[])
{
	printf("SIGRTMIN = %d, LIBC_SIGRTMIN = %d\n", SIGRTMIN, LIBC_SIGRTMIN);
	printf("SIGRTMAX = %d, LIBC_SIGRTMAX = %d\n", SIGRTMAX, LIBC_SIGRTMAX);
	return 0;
}
