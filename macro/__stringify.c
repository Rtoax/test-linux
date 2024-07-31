#include <stdio.h>

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

#define NUM	3

int main(void)
{
	printf("NUM = %s\n", __stringify(NUM));
	return 0;
}

