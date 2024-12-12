#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

#ifndef NR_THREADS
#define NR_THREADS	1
#endif

sig_atomic_t loop = true;
const int us = 100000;

void sig_handler(int signum)
{
	printf("Catch signal.\n");
	loop = false;
}

void print_ansi(void)
{
	fprintf(stderr, "\033[31mx\033[m");
	usleep(us);
}

void *print_xs(void *unused)
{
	pthread_setname_np(pthread_self(), "pthread-child");

	while (loop)
		print_ansi();
	return NULL;
}

int main(void)
{
	int i;
	pthread_t threads[NR_THREADS];

	signal(SIGINT, sig_handler);

	for (i = 0; i < NR_THREADS; i++)
		pthread_create(&threads[i], NULL, &print_xs, NULL);

	pthread_setname_np(pthread_self(), "pthread-parent");

	while (loop) {
		fputc('o', stderr);
		usleep(us);
	}

	for (i = 0; i < NR_THREADS; i++)
		pthread_join(threads[i], NULL);

	return 0;
}
