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

int main()
{
	vfork();
	/**
	 * Children in interruptible sleep
	 * Parent in uninterruptible sleep
	 */
	sleep(60);
	return 0;
}
