#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int count = 0;

	while (++count) {
		printf("count  = %d\n", count);
		sleep(1);
	}

	return 0;
}
