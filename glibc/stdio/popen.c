#include <stdio.h>
#include <unistd.h>

int ps(int argc, char *argv[])
{
	char cmd[256] = {0};
	char line[256] = {0};
	FILE *fp;

	sprintf(cmd, "ps -aux");
	fp = popen(cmd, "r");

	while (fgets(line, 256, fp))
		printf("%s\n", line);

	pclose(fp);
	return 0;
}

int sort(void)
{
	FILE *stream = popen("sort", "w");

	fprintf(stream, "This is a test.\n");
	fprintf(stream, "Hello, world.\n");
	fprintf(stream, "My dog has fleas.\n");
	fprintf(stream, "This program is great.\n");
	fprintf(stream, "One fish, two fish.\n");

	return pclose(stream);
}

int main(void)
{
	ps(0, NULL);
	sort();
	return 0;
}
