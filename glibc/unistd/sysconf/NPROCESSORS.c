#include <stdio.h>
#include <unistd.h>


int main(void)
{
	int ncpu;

	/* processors configured */
	ncpu = sysconf(_SC_NPROCESSORS_CONF);
	printf("_SC_NPROCESSORS_CONF: ncpu = %d\n", ncpu);

	/* processors available */
	ncpu = sysconf(_SC_NPROCESSORS_ONLN);
	printf("_SC_NPROCESSORS_ONLN: ncpu = %d\n", ncpu);
	return 0;
}
