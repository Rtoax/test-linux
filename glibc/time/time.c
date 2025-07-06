#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t t;
	time(&t);
	printf("time: %ld\n", t);
	return 0;
}
