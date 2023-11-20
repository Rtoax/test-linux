#include <stdio.h>
#include <unistd.h>


int main(void)
{
	daemon(1, 1);

	while (1) {
		printf("--->\n");
		sleep(1);
	}
	return 0;
}

