#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(msg) do { \
		perror(msg);\
		exit(-1);\
	} while (0)

int set_nonblock_flag(int desc, int value)
{
    int oldflags = fcntl(desc, F_GETFL, 0);
    if (oldflags == -1)
        return -1;

    if (value != 0)
        oldflags |= O_NONBLOCK;
    else
        oldflags &= ~O_NONBLOCK;

    return fcntl(desc, F_SETFL, oldflags);
}

int main(void)
{
	int fd = fileno(stdout);
	char s[10];
	struct flock f;
	memset(s, 0, 10);
	sprintf(s, "Hello R\n");
	write(fd, &s, 10);

	int fd1 = open("test.dat", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0) {
		ERR_EXIT("openfile error");
	}

	memset(&f, 0, sizeof(struct flock));

	f.l_type = F_WRLCK;
	f.l_whence = SEEK_SET;
	f.l_start = 0;
	f.l_len = 0;

	write(fd1, "RongTao\nasdf\n", 14);

	if (fcntl(fd, F_SETLK, &f) < 0) {
		ERR_EXIT("lock error");
	}

	f.l_type = F_UNLCK;

	if (fcntl(fd, F_SETLK, &f) < 0) {
		ERR_EXIT("unlock error");
	}

	/* F_GETFD, F_SETFD */
	int stdoutno = fileno(stdout);
	int flagout = fcntl(stdoutno, F_GETFD, 0);
	int newno = fcntl(stdoutno, F_SETFD, flagout);

	printf("stdoutno = %d, flagout = %d, newno = %d\n", stdoutno, flagout, newno);

	return 0;
}
