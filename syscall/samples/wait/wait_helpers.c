// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "wait_helpers.h"

void print_wstatus(int status)
{
	printf("WIFEXITED(%d=0x%x)	= %d\n", status, status, WIFEXITED(status));
	printf("WEXITSTATUS(%d=0x%x)	= %d\n", status, status, WEXITSTATUS(status));
	printf("WTERMSIG(%d=0x%x)	= %d\n", status, status, WTERMSIG(status));
	printf("WSTOPSIG(%d=0x%x)	= %d\n", status, status, WSTOPSIG(status));
	printf("WIFSIGNALED(%d=0x%x)	= %d\n", status, status, WIFSIGNALED(status));
	printf("WIFSTOPPED(%d=0x%x)	= %d\n", status, status, WIFSTOPPED(status));
	printf("WCOREDUMP(%d=0x%x)	= %d\n", status, status, WCOREDUMP(status));
	printf("WIFCONTINUED(%d=0x%x)	= %d\n", status, status, WIFCONTINUED(status));
}
