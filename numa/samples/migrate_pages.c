#include <stdio.h>
#include <numa.h>
#include <numaif.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int ret;
	char *str;
	unsigned long old_nodes = 0;
	unsigned long new_nodes = 1;

	str = numa_alloc(numa_pagesize());
	printf("numa_max_node = %d\n", numa_max_node());

	ret = migrate_pages(getpid(), numa_max_node(), &old_nodes, &new_nodes);
	printf("migrate_pages ret %d\n", ret);
	perror("migrate_pages: ");
	printf("EPERM = %d\n", EPERM);
	printf("ESRCH = %d\n", ESRCH);

	numa_free(str, numa_pagesize());

	return 0;
}

