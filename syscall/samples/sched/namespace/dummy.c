#include <stdio.h>
#include <unistd.h>

int main(void)
{
	unsigned long count = 0;
	while (1) {
		printf("Sleeping %ld s\n", count++);
		sleep(1);
	}
	return 0;
}
