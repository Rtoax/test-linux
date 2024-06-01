#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <sched.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t child_mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int child_waiting = 0;
double endtime;

double usec(void)
{
	int retval;
	struct timeval tv;

	retval = gettimeofday(&tv, NULL);
	if (retval != 0) {
		perror("gettimeofday");
		exit(-1);
	}
	return (tv.tv_sec * 1000000.0 + ((double)tv.tv_usec));
}

void *childfunc(void *arg)
{
	pthread_cond_t *cp = (pthread_cond_t *)arg;

	while (child_waiting == 0) {
		pthread_mutex_lock(&child_mutex);
		child_waiting = 1;
		if (pthread_cond_wait(cp, &child_mutex) != 0) {
			perror("pthread_cond_wait");
			exit(-1);
		}
		endtime = usec();
		child_waiting = 2;
		pthread_mutex_unlock(&child_mutex);
		while (child_waiting == 2) {
			poll(NULL, 0, 10);
		}
	}
	pthread_exit(NULL);
}

void test_signal(int broadcast_flag, int iter)
{
	pthread_attr_t attr;
	pthread_t childid;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	int i;
	int prio;
	struct sched_param schparm;
	double starttime;

	prio = sched_get_priority_max(SCHED_FIFO);
	if (prio == -1) {
		perror("sched_get_priority_max");
		exit(-1);
	}
	schparm.sched_priority = prio;
	if (sched_setscheduler(getpid(), SCHED_FIFO, &schparm) != 0) {
		perror("sched_setscheduler");
		exit(-1);
	}

	if (pthread_attr_init(&attr) != 0) {
		perror("pthread_attr_init");
		exit(-1);
	}
	if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
		perror("pthread_attr_setschedpolicy");
		exit(-1);
	}
	if (pthread_attr_setschedparam(&attr, &schparm) != 0) {
		perror("pthread_attr_setschedparam");
		exit(-1);
	}
	if (pthread_create(&childid, &attr, childfunc, (void *)&cond) != 0) {
		perror("pthread_create");
		exit(-1);
	}
	for (i = 0; i < iter; i++) {
		pthread_mutex_lock(&child_mutex);
		child_waiting = 0;
		while (child_waiting == 0) {
			pthread_mutex_unlock(&child_mutex);
			sched_yield();
			pthread_mutex_lock(&child_mutex);
		}
		pthread_mutex_unlock(&child_mutex);
		if (broadcast_flag) {
			starttime = usec();
			if (pthread_cond_broadcast(&cond) != 0) {
				perror("pthread_cond_broadcast");
				exit(-1);
			}
		} else {
			starttime = usec();
			if (pthread_cond_signal(&cond) != 0) {
				perror("pthread_cond_signal");
				exit(-1);
			}
		}
		for (;;) {
			pthread_mutex_lock(&child_mutex);
			if (child_waiting == 2) {
				break;
			}
			pthread_mutex_unlock(&child_mutex);
			poll(NULL, 0, 10);
		}
		printf("%s() latency: %d us\n",
		       (broadcast_flag
			? "pthread_cond_broadcast"
			: "pthread_cond_signal"),
		       (int)(endtime - starttime));
		pthread_mutex_unlock(&child_mutex);
	}
	pthread_mutex_lock(&child_mutex);
	child_waiting = 3;
	pthread_mutex_unlock(&child_mutex);
	if (pthread_join(childid, NULL) != 0) {
		perror("pthread_join");
		exit(-1);
	}
}

int main(int argc, char *argv[])
{
	struct sched_param sp;
	long iter;

	sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
	if (sp.sched_priority == -1) {
		perror("sched_get_priority_max");
		exit(-1);
	}
	if (sched_setscheduler(0, SCHED_FIFO, &sp) != 0) {
		perror("sched_setscheduler");
		exit(-1);
	}

	if (argc == 1) {
		fprintf(stderr, "WARNING: Usage: %s iterations\n", argv[0]);
		iter = 10;
	} else {
		iter = strtol(argv[1], NULL, 0);
	}
	test_signal(0, iter);
	test_signal(1, iter);

	return 0;
}

