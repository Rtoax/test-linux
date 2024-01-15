#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_proc_pid_maps(void)
{
	char cmd[128];
	pid_t pid = getpid();
	snprintf(cmd, sizeof(cmd) - 1, "cat /proc/%d/maps", pid);
	system(cmd);
}

