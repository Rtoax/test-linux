#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NR_THREAD	30

struct data_t {
	char *str;
	size_t len;
	size_t count;
};

void *thread_race(void *arg)
{
#define RACE
#ifdef RACE
	struct data_t *data = arg;
	while (data->count <= 10) {
		data->count++;
		printf("%16ld %ld\n", pthread_self(), data->count);
	}
#endif

	return 0;
}

int main(void)
{
	int i;
	char *str;
	struct data_t data;
	pthread_t thread[NR_THREAD];

	str = (char *)malloc(1024);

	data.str = str;
	data.len = 1024;
	data.count = 0;

	for (i = 0; i < NR_THREAD; i++)
		pthread_create(&thread[i], NULL, thread_race, &data);

	for (i = 0; i < NR_THREAD; i++)
		pthread_join(thread[i], NULL);

	return 0;
}
