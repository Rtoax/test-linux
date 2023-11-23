#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/stat.h>


#define MAP_FILENAME	"/etc/os-release"

int fd;

void sig_handler(int signo)
{
	close(fd);
	exit(0);
}

int main(void)
{
	int i, ret;
	char *p;
	struct stat st;

	signal(SIGINT, sig_handler);

	fd = open(MAP_FILENAME, O_RDONLY);
	if (fd == -1) {
		perror("open\n");
		exit(1);
	}
	ret = stat(MAP_FILENAME, &st);
	if (ret == -1) {
		perror("stat");
		exit(1);
	}

	p = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap\n");
		exit(1);
	}

	for (i = 0; i < st.st_size; i++) {
		char ch = *(p + i);
		putchar(ch);
	}

	sig_handler(0);

	return 0;
}

