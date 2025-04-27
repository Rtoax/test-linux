#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "memfd_helpers.h"


int main(void)
{
	int fd;
	pid_t child;
	char buf[BUFSIZ] = "";
	ssize_t br;

	fd = sys_memfd_create("foofile", 0);
	if (fd == -1) {
		perror("memfd_create");
		exit(EXIT_FAILURE);
	}

	child = fork();
	if (child == 0) {
		/* Duplicate memfd to stdout */
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execlp("/bin/date", "", NULL);
		perror("execlp date");
		exit(EXIT_FAILURE);
	} else if (child == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	waitpid(child, NULL, 0);

	/* Read from memfd */
	lseek(fd, 0, SEEK_SET);
	br = read(fd, buf, BUFSIZ);
	if (br == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buf[br] = 0;

	printf("pid:%d\n", getpid());
	printf("child said: '%s'\n", buf);
	exit(EXIT_SUCCESS);
}
