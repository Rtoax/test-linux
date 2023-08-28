#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>


static const char *filename = "testfile";
static int try_times = 10;

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
		fprintf(stderr, "[%s:%d] flock: %s\n", prefix, gettid(),
				strerror(errno));
		close(fd);
		return -1;
	}

	write(fd, msg, strlen(msg));

	flock(fd, LOCK_UN);
	close(fd);

	return 0;
}

void *task_routinue(void *arg)
{
	int try = try_times;
	char buffer[1024];

	snprintf(buffer, sizeof(buffer), "I am %d\n", gettid());
	printf("%s", buffer);

	while (try-- &&
		!open_and_write(filename, "Thread", buffer));

	return NULL;
}

int main(void)
{
#define NR_THREADS	2
	int i, fd;
	pthread_t *threads;

	threads = malloc(sizeof(pthread_t) * NR_THREADS);

	/* Create the testfile. */
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(fd, "hello\n", sizeof("hello\n"));
	close(fd);

	for (i = 0; i < NR_THREADS; i++) {
		pthread_create(&threads[i], NULL, task_routinue, NULL);
	}

	for (i = 0; i < NR_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	free(threads);
	return 0;
}
