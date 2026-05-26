#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *buf;

	printf("%f\n", strtof("123.34asdf", &buf));
	printf("%s\n", buf);
	if (argc > 1) {
		printf("strtof(%s) = %f\n", argv[1], strtof(argv[1], &buf));
	}

	return 0;
}
