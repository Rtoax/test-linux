#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define NR_THREADS	5

static sig_atomic_t loop = true;

void sig_handler(int signum)
{
	printf("Catch signal.\n");
	loop = false;
}

void open_write_close(void)
{
	char file[128];
	int fd, n;

	snprintf(file, sizeof(file), "tmp-%d.bin", gettid());

	fd = open(file, O_CREAT | O_RDWR, 0666);
	if (fd == -1) {
		fprintf(stderr, "ERROR: open(%s) %m\n", file);
		return;
	}

	n = write(fd, file, strlen(file));
	if (n == -1) {
		fprintf(stderr, "ERROR: write(%s) %m\n", file);
		close(fd);
		return;
	}

#ifdef ERROR
	close(fd);
#endif
	usleep(1000); /* Pretend to do something... */
	close(fd);
}

void *thread_fn(void *unused)
{
	pthread_setname_np(pthread_self(), "pthread-child");

	while (loop)
		open_write_close();
	return NULL;
}

int main(int argc, char *argv[])
{
	int i;
	pthread_t threads[NR_THREADS];

	signal(SIGINT, sig_handler);

	for (i = 0; i < NR_THREADS; i++)
		pthread_create(&threads[i], NULL, &thread_fn, NULL);

	pthread_setname_np(pthread_self(), "pthread-parent");

	for (i = 0; i < NR_THREADS; i++)
		pthread_join(threads[i], NULL);

	return 0;
}
