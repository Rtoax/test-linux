#include <stdio.h>
#include <unistd.h>

unsigned long count = 0;

int main(void)
{
	while (1)
#ifdef WHILE_SLEEP
	{
		printf("count %ld\n", count++);
		sleep(1);
	}
#endif
		;
	return 0;
}
