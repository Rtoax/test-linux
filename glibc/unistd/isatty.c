#include <stdio.h>
#include <unistd.h>

int main(void)
{
	FILE *fp = fopen("tmp.out", "w");

	printf("%s: %d\n", ttyname(fileno(stdin)), isatty(fileno(stdin)));
	printf("%s: %d\n", ttyname(fileno(stdout)), isatty(fileno(stdout)));
	printf("%s: %d\n", ttyname(fileno(stderr)), isatty(fileno(stderr)));
	printf("%s: %d\n", ttyname(fileno(fp)), isatty(fileno(fp)));

	fclose(fp);

	return 0;
}

