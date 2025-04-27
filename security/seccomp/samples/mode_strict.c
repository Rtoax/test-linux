#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <linux/seccomp.h>

#include "seccomp_helpers.h"

/* SIGKILL not in here. */
void sig_handler(int signum)
{
	printf("Catch SIGnal.\n");
	exit(1);
}

void set_mode_strict(void)
{
	/* same as: prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT); */
	sys_seccomp(SECCOMP_SET_MODE_STRICT, 0, NULL);
}

int main(int argc, char* argv[])
{
	signal(SIGKILL, sig_handler);

	printf("Install seccomp\n");
	set_mode_strict();

	/* only allow read, write, _exit syscall, see seccomp(2) */
	char buf[] = "Hello World\n";
	write(1, buf, sizeof(buf));

	printf("Creating socket\n");
	/* This process will be killed here: SIGKILL. */
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	return 0;
}
