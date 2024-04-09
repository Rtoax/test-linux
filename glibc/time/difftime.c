#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
	time_t t0, t1;

	t0 = time(NULL);
	usleep(1000000);
	t1 = time(NULL);

	printf("%lf\n", difftime(t1, t0));

	return 0;
}
