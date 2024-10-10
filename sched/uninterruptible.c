/**
 * File: uninterruptible.c
 *
 * $ gcc uninterruptible.c -o uninterruptible.out
 * $ ps -o ppid,pid,stat,cmd $(pgrep -f uninterruptible.out)
 * $ for ((i=0;i<100;i++)); do ./uninterruptible.out & done
 * $ uptime
 *
 * Ref: https://unix.stackexchange.com/questions/134888/simulate-an-unkillable-process-in-d-state
 */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void vfork_sleep(int secs)
{
	pid_t pid = vfork();
	/**
	 * Children in interruptible sleep
	 * Parent in uninterruptible sleep
	 */
	sleep(secs);

	if (pid > 0) {
		waitpid(pid, NULL, 0);
	} else if (pid == 0) {
		exit(0);
	}
}

void usage(int argc, char *argv[])
{
	printf("usage: [option].\n");
	printf(" %s vfork-sleep [sleep sec(60 by default)]: use vfork() sleep() generate D task.\n", argv[0]);
	printf("\n");
	printf(" run the following cmd to make plenty of D tasks.\n");
	printf(" $ for ((i=0;i<100;i++)); do %s vfork-sleep [secs] & done\n", argv[0]);
	exit(0);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		usage(argc, argv);
	}
	if (!strcmp(argv[1], "vfork-sleep")) {
		int secs = argc == 3 ? atoi(argv[2]) : 60;
		vfork_sleep(secs ?: 60);
	} else {
		usage(argc, argv);
	}
	return 0;
}
