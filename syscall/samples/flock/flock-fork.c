#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>

#include "flock_helpers.h"


int main(void)
{
	int fd;
	pid_t pid;

	const char *filename = "testfile";

	/* Create the testfile. */
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(fd, "hello\n", sizeof("hello\n"));
	close(fd);

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Failed fork\n");
		exit(1);
	}

	/* Children */
	if (pid == 0) {
		int try_times = 10;
		while (try_times-- &&
		       !open_and_write_with_lock(filename, "Child",
				   "hello from child.\n")) ;
		exit(0);
	}

	/* Father */
	int try_times = 10;
	while (try_times-- &&
	       !open_and_write_with_lock(filename, "Father",
				  "hello from parent.\n")) ;
	wait(NULL);
	return 0;
}
