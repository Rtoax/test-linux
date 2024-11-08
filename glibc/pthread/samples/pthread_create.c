#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

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

	while (loop) {
		print_ansi();
	}

	return NULL;
}

int main(void)
{
	pthread_t thread_id;

	signal(SIGINT, sig_handler);
	pthread_create(&thread_id, NULL, &print_xs, NULL);

	pthread_setname_np(pthread_self(), "pthread-parent");
	while (loop) {
		fputc('o', stderr);
		usleep(us);
	}

	pthread_join(thread_id, NULL);

	return 0;
}
