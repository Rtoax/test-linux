#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;
	FILE *fp;

	fp = fopen("/sys/block/sda/stat", "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen %m\n");
		exit(1);
	}

	/* segv here if none parameters be specified */
	i = fscanf(fp, "%lu %lu %lu %lu %lu %lu %lu %u %u %u %u %lu %lu %lu %u %lu %u");
	printf("i = %d\n", i);

	return 0;
}
