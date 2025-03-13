#include <stdio.h>
#include <unistd.h>


int main(void)
{
	int cnt = 3;

	daemon(1, 1);

	while (cnt--) {
		printf("daemon running...\n");
		sleep(1);
	}
	printf("daemon exit\n");
	return 0;
}

