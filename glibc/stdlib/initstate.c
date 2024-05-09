#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#define __unused __attribute__((unused))

int main(void)
{
	int i, j, *b;
	char buf[256];
	struct random_data __unused *data;

	data = (struct random_data *)initstate(time(NULL), (char *)&buf, 256);

	j = 256 / sizeof(int) * sizeof(char);
	printf("j = %d\n", j); /* FIXME: SIGABRT if no this line */
	b = malloc(j);

	memcpy(b, buf, 256);

	for (i = 0; i < j; i++)
		printf("%d, ", b[i]);
	printf("\n");

	return 0;
}
