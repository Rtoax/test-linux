#include <stdio.h>
#include <pthread.h>

#include "pthread_helpers.h"

struct args {
	int cpu;
};

void *loop(void *arg)
{
	struct thread *t = arg;
	struct args *a = (struct args *)t->arg;

	fprintf(stderr, "Try set cpu affinity %d\n", a->cpu);
	sys_affinity_bind(a->cpu);
	while (true) ;
	return NULL;
}

int main(void)
{
	struct thread *threads[3];

	struct args args[3] = {
		{
		 .cpu = 1,
		 },
		{
		 .cpu = 2,
		 },
		{
		 .cpu = 3,
		 },
	};

	threads[0] = create_fifo_thread(loop, &args[0], 99);
	threads[1] = create_rr_thread(loop, &args[1], 99);
	threads[2] = create_other_thread(loop, &args[2]);
	if (!threads[0] || !threads[1] || !threads[2])
		goto failed;

	pthread_join(threads[0]->pthread, NULL);
	pthread_join(threads[1]->pthread, NULL);
	pthread_join(threads[2]->pthread, NULL);

	return 0;
 failed:
	return -1;
}
