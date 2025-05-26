#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int count = 0;

	while (1) {
		printf("hello linux! count = %d\n", count++);
		fflush(stdout);
		sleep(1);
	}
	return 0;
}
