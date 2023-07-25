#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>


/**
 * duplicate file descriptors (created by, for example, fork(2) or dup(2))
 * refer to the same lock. (see flock(2))
 */
int open_and_write(const char *filename, const char *prefix, const char *msg)
{
	int ret;
	int fd = open(filename, O_TRUNC | O_RDWR, 0644);

	ret = flock(fd, LOCK_EX | LOCK_NB);
	if (ret != 0) {
		fprintf(stderr, "[%s] flock: %s\n", prefix, strerror(errno));
		close(fd);
		return -1;
	}

	write(fd, msg, strlen(msg));

	flock(fd, LOCK_UN);

	return 0;
}

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
	/* Children */
	if (pid == 0) {

		while (!open_and_write(filename, "Child", "hello from child.\n"));

		exit(0);

	/* Father */
	} else if (pid > 0) {

		while (!open_and_write(filename, "Father", "hello from parent.\n"));

		wait(NULL);

	} else {
		fprintf(stderr, "Failed fork\n");
		exit(1);
	}

	return 0;
}
