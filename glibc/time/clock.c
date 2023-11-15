#include <time.h>
#include <stdio.h>
#include <unistd.h>


int main(void)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	/* Do the work. */
	sleep(1);
	end = clock();

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("CLOCK_PER_SEC: %ld\n", CLOCKS_PER_SEC);
	printf("clocks: %lf\n", cpu_time_used);
	return 0;
}
