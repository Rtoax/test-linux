#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>


bool loop = true;
void sig_handler(int signum)
{
	printf("Catch signal.\n");
	loop = false;
}

void* print_xs(void* unused)
{
	while (loop) {
		fputc('x', stderr);
		usleep(1000);
	}

	return NULL;
}

int main(void)
{
	pthread_t thread_id;

	signal(SIGINT, sig_handler);
	pthread_create(&thread_id, NULL, &print_xs, NULL);

	while (loop) {
		fputc('o', stderr);
		usleep(1000);
	}

	pthread_join(thread_id, NULL);

	return 0;
}
