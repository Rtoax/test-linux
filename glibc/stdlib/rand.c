#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

static inline unsigned long getrand(unsigned long max)
{
	return (unsigned long)(max * 1.0 * rand() / RAND_MAX + 1.0);
}

int main(void)
{
#ifdef SRAND
	srand(nsecs());
#endif

	int i, j;
	for (i = 1; i <= 3000; i++) {
		j = getrand(10);
		printf("%3d", j);
		if (i % 30 == 0)
			printf("\n");
	}

	printf("RAND_MAX = %d\n", RAND_MAX);

	return 0;
}
