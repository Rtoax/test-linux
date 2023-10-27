#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <linux/seccomp.h>

/* SIGKILL not in here. */
void sig_handler(int signum)
{
	printf("Catch SIGnal.\n");
	exit(1);
}

int main(int argc, char* argv[])
{
	signal(SIGKILL, sig_handler);

	printf("Install seccomp\n");
	prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);

	printf("Creating socket\n");

	/* This process will be killed here: SIGKILL. */
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	return 0;
}
