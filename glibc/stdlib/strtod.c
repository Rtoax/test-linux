#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *buf;

	printf("%f\n", strtod("123.34asdf", &buf));
	printf("%s\n", buf);
	if (argc > 1) {
		printf("strtod(%s) = %lf\n", argv[1], strtod(argv[1], &buf));
	}

	return 0;
}
