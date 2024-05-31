#include <pthread.h>
#include <stdio.h>

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2;

int main(void)
{
	pthread_cond_init(&cond2, NULL);
	pthread_cond_destroy(&cond2);
	return 0;
}

