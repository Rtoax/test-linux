#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *buf;
	char *bufs[] = {
		"123.34asdf",
		"0",
		".123",
		"-1;",
	};

	for (int i = 0; i < sizeof(bufs) / sizeof(bufs[0]); i++) {
		printf("strtod(\"%s\") = %f", bufs[i], strtod(bufs[i], &buf));
		printf("\t%s\n", buf);
	}

	for (int i = 1; i < argc; i++) {
		printf("strtod(\"%s\") = %lf", argv[i], strtod(argv[i], &buf));
		printf("\t%s\n", buf);
	}

	return 0;
}
