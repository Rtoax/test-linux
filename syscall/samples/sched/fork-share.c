#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int fd1;
	int fd2;
	const char *file = "test.txt.out";
	char str[] = "-------------communication!----------\n";

	pid = fork();

	if (pid == -1) {
		perror("fork!");
		exit(1);

	} else if (pid == 0) {

		fd1 = open(file, O_RDWR | O_CREAT, 0660);
		if (fd1 == -1) {
			perror("open!");
			exit(1);
		}
		write(fd1, str, sizeof(str));
		printf("child close! \n");

	} else {

		sleep(1);

		fd2 = open(file, O_RDWR);
		if (fd2 == -1) {
			perror("open!");
			exit(1);
		}

		sleep(1);

		int buf[1024];
		int len = read(fd2, buf, sizeof(buf));

		write(STDOUT_FILENO, buf, len);

		wait(NULL);
	}
	return 0;
}

