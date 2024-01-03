#include <stdio.h>
#include <sched.h>

int main(void)
{
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(8, &cpuset);
	if (CPU_ISSET(8, &cpuset))
		printf("set 8\n");

	CPU_CLR(8, &cpuset);
	if (CPU_ISSET(8, &cpuset))
		printf("set 8\n");

	return 0;
}
