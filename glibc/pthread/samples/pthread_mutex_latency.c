#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
volatile unsigned long ticks_start = 0;
volatile unsigned long ticks_end = 0;

static struct cpu_freq {
	enum {
		CPU_3GMHZ, CPU_2_7GMHZ,
	} index;
	unsigned long freq;
	char *string;
} CPU_MHZ[] = {
	{CPU_3GMHZ, 3000000000, "3GMHz"},
	{CPU_2_7GMHZ, 2700000000, "2.7GMHz"},
};

unsigned long get_x84_64_ticks(void)
{
	unsigned long ret;
	union {
		unsigned long tsc_64;
		struct {
			unsigned int lo_32;
			unsigned int hi_32;
		};
	} tsc;
	__asm volatile ("rdtsc": "=a" (tsc.lo_32), "=d"(tsc.hi_32));
	ret = ((unsigned long)tsc.tsc_64);
	return ret;
}

void *task_hold_mutex(void *unused)
{
	printf("task_hold_mutex.\n");
	pthread_mutex_lock(&mutex1);

	sleep(1);
	ticks_start = get_x84_64_ticks();

	pthread_mutex_unlock(&mutex1);
	pthread_exit(NULL);
	return NULL;
}

void *task_get_mutex(void *unused)
{
	printf("task_get_mutex.\n");

	sleep(1);
	pthread_mutex_lock(&mutex1);
	ticks_end = get_x84_64_ticks();

	pthread_mutex_unlock(&mutex1);

	pthread_exit(NULL);
	return NULL;
}

int main(void)
{
	pthread_t t1, t2;

	pthread_mutex_init(&mutex1, NULL);

	pthread_create(&t1, NULL, task_hold_mutex, NULL);
	pthread_create(&t2, NULL, task_get_mutex, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mutex1);

	printf("Latency = %lf ms\n",
	       (ticks_end -
		ticks_start) * 1.0 / CPU_MHZ[CPU_2_7GMHZ].freq * 1000.0);

	return 0;
}
