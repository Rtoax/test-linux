#include <stdio.h>

int main(void)
{
	__label__ loop;
	int times = 0;
 loop:
	if (times++ < 5) {
		printf("times = %d\n", times);
		goto loop;
	}
	return 0;
}
