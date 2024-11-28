#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <numa.h>
#include <numaif.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

int main(void)
{
	long i, ret, numa, cpu, size;
	char *str;
	int nr_nodes;
	unsigned long old_nodes;
	unsigned long new_nodes;

	cpu = sched_getcpu();
	numa = numa_node_of_cpu(cpu);
	nr_nodes = numa_max_node();

	size = numa_pagesize() * 1024;

	if (nr_nodes == 1) {
		fprintf(stderr, "WARNING: Only one NUMA on this system.\n");
		exit(0);
	}

	printf("NUMA number %d, run on cpu %ld (numa %ld)\n", nr_nodes, cpu,
		numa);

	str = numa_alloc(size);

	/* Page fault */
	for (i = 0; i < size; i += numa_pagesize())
		str[i] = 'a';

	/**
	 * Migrate pages to that NUMA i run on.
	 */
	old_nodes = 0;
	new_nodes = numa;

	ret = migrate_pages(getpid(), nr_nodes, &old_nodes, &new_nodes);
	if (ret > 0)
		printf("%ld pages could not be moved.\n", ret);
	else
		perror("migrate_pages");

	numa_free(str, size);

	return 0;
}

