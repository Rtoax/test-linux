#include <stdio.h>


int fgets_file(const char *file)
{
	char str[123] = {0};
	FILE *fp = fopen(file, "r");

	while (fgets(str, sizeof(str), fp))
		printf("%s", str);

	fclose(fp);
	return 0;
}

int main(void)
{
	fgets_file("/etc/os-release");
	fgets_file("/proc/self/maps");
	return 0;
}
