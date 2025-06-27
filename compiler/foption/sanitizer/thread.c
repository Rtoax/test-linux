#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NR_THREAD	2
#define NR_LOOP	1

//#define LOCK
#ifdef LOCK
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define my_lock() pthread_mutex_lock(&mutex)
#define my_unlock() pthread_mutex_unlock(&mutex)
#else
#define my_lock()
#define my_unlock()
#endif


struct data_t {
	char *str;
	size_t len;
	size_t count;
	size_t loop;
};

void *thread_race(void *arg)
{
	int i = 0;
	struct data_t *data = arg;
	while (i++ < NR_LOOP) {
		sleep(1);
		my_lock();
		data->count++;
		data->str[0] = 'a';
		printf("%16ld %ld\n", pthread_self(), data->count);
		my_unlock();
	}

	return 0;
}

int racecall(void)
{
	int i;
	size_t len = 0x10000;
	char *str;
	struct data_t data;
	pthread_t thread[NR_THREAD];
	str = (char *)malloc(len);

	data.str = str;
	data.len = len;
	data.count = 0;
	data.loop = 1;

	for (i = 0; i < NR_THREAD; i++)
		pthread_create(&thread[i], NULL, thread_race, &data);

	for (i = 0; i < NR_THREAD; i++)
		pthread_join(thread[i], NULL);
	free(str);

	return 0;
}

int main(void)
{
	int i;
	for (i = 0; i < 1000000000; i++)
		racecall();
	return 0;
}
