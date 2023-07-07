#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <fcntl.h>

/**
 * stdout          [0]                   [1]
 *     |  splice   +-----------------------+   splice
 *     +----+------|   pipefd_stdout       |<--------------stdin
 *          |      +-----------------------+
 *          |
 *          |tee
 *          |      [1]                   [0]
 *          |      +-----------------------+   splice
 *          +----->|   pipefd_file         |--------------> filefd = open("file.txt", ...);
 *                 +-----------------------+
 *
 * $ cat /etc/os-release | ./tee2 | cat
 */

int main(int argc,const char* argv[])
{
	int pipefd_stdout[2];
	int pipefd_file[2];
	int filefd;
	int ret;


	filefd = open("tee.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if (filefd <= 0) {
		perror("open:");
		exit(EXIT_FAILURE);
	}

	ret = pipe(pipefd_stdout);
	if (ret != 0) {
		perror("pipe:");
		exit(EXIT_FAILURE);
	}
	ret = pipe(pipefd_file);
	if (ret != 0) {
		perror("pipe:");
		exit(EXIT_FAILURE);
	}

	/* splice stdin to pipefd_stdout */
	ret = splice(STDIN_FILENO, NULL, pipefd_stdout[1], NULL, 32768, SPLICE_F_MORE|SPLICE_F_MOVE);
	if (ret <= 0) {
		perror("splice stdin to pipefd_stdout:");
		exit(EXIT_FAILURE);
	}

	/* tee pipefd_stdout[0] to pipefd_file */
	ret = tee(pipefd_stdout[0], pipefd_file[1], 32768, SPLICE_F_NONBLOCK);
	if (ret <= 0) {
		perror("tee:");
		exit(EXIT_FAILURE);
	}

	/* splice pipefd_file to filefd */
	ret = splice(pipefd_file[0], NULL, filefd, NULL, 32768, SPLICE_F_MORE);
	if (ret <= 0) {
		perror("splice pipefd_file to filefd:");
		exit(EXIT_FAILURE);
	}

	/* splice pipefd_stdout to stdout */
	ret = splice(pipefd_stdout[0], NULL, STDOUT_FILENO, NULL, 32768, SPLICE_F_MORE|SPLICE_F_MOVE);
	if (ret <= 0) {
		perror("splice pipefd_stdout to stdout:");
		exit(EXIT_FAILURE);
	}

	close(filefd);
	close(pipefd_file[0]);
	close(pipefd_file[1]);
	close(pipefd_stdout[0]);
	close(pipefd_stdout[1]);

	return 0;
}

