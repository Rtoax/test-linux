#include <stdio.h>
#include <unistd.h>


int main(void)
{
	int ncpu;

	ncpu = sysconf(_SC_NPROCESSORS_CONF);
	printf("ncpu = %d\n", ncpu);

	ncpu = sysconf(_SC_NPROCESSORS_ONLN);
	printf("ncpu = %d\n", ncpu);
	return 0;
}
