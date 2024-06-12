#include <stdio.h>

int main(void)
{
	char cmd[123] = {0};
	FILE *fp = fopen("/etc/os-release", "r");

	while (fgets(cmd, 123, fp))
		printf("%s", cmd);

	fclose(fp);
	return 0;
}
