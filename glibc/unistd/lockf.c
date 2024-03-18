#include <stdio.h>
#include <unistd.h>

#ifdef NO_LOCK
#define lockf(a,b,c) do {} while (0)
#endif

static int us = 10000;

int main(void)
{
	int p1, p2, i;
#ifndef NO_LOCK
	int fd = fileno(stdout);
#endif

	while ((p1 = fork()) == -1);
	if (p1 == 0) {
		lockf(fd, 1, 0);
		for (i = 0; i < 5; i++) {
			printf("daughter:%d\n",i);
			usleep(us);
		}
		lockf(fd, 0, 0);
	} else {
		while ((p2 = fork()) == -1);
		if (p2 == 0) {
			lockf(fd, 1, 0);
			for (i = 0; i < 5; i++) {
				printf("son:%d\n",i);
				usleep(us);
			}
			lockf(fd, 0, 0);
		} else {
			lockf(fd, 1, 0);
			for (i = 0; i < 5; i++) {
				printf("parent:%d\n",i);
				usleep(us);
			}
			lockf(fd, 0, 0);
		}
	}
	return 0;
}

