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
#define MAP_FILENAME_OUT	"os-release"

int fd, fdout;

void sig_handler(int signo)
{
	close(fd);
	close(fdout);
	exit(0);
}

int main(void)
{
	int i, ret;
	char *p, *pout;
	struct stat st;

	signal(SIGINT, sig_handler);

	fd = open(MAP_FILENAME, O_RDONLY);
	if (fd == -1) {
		perror("open\n");
		exit(1);
	}
	fdout = open(MAP_FILENAME_OUT, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1) {
		perror("open\n");
		exit(1);
	}

	ret = stat(MAP_FILENAME, &st);
	if (ret == -1) {
		perror("stat");
		exit(1);
	}

	ftruncate(fdout, st.st_size);

	p = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap\n");
		exit(1);
	}
	pout = mmap(NULL, st.st_size, PROT_WRITE|PROT_READ, MAP_SHARED, fdout, 0);
	if (pout == MAP_FAILED) {
		perror("mmap\n");
		exit(1);
	}

	for (i = 0; i < st.st_size; i++) {
		char ch = *(p + i);
		putchar(ch);
		pout[i] = ch;
	}

	sig_handler(0);

	return 0;
}

