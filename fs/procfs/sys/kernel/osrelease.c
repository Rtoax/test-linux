#include <stdio.h>

void parse_version(void)
{
	int a1, a2, a3;
	FILE *fp = fopen("/proc/sys/kernel/osrelease", "r");

	if (fp == NULL || fscanf(fp, "%d.%d.%d", &a1, &a2, &a3) != 3)
		return;

	printf("actual %d %d %d\n", a1, a2, a3);

	fclose(fp);
}

int main(void)
{
	parse_version();
	return 0;
}
