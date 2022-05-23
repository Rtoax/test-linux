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

void vfork_sleep(int secs)
{
	vfork();
	/**
	 * Children in interruptible sleep
	 * Parent in uninterruptible sleep
	 */
	sleep(secs);
}

void usage(void)
{
	printf("usage: [option].\n");
	printf(" vfork-sleep [sleep sec(60 by default)]: use vfork() sleep() generate D task.\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		usage();
	}
	if (!strcmp(argv[1], "vfork-sleep")) {
		int secs = argc==2?atoi(argv[2]):60;
		vfork_sleep(secs?:60);
	} else {
		usage();
	}
	return 0;
}
