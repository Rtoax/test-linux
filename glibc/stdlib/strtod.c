#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *buf;
	char *bufs[] = {
		"123.34asdf", "0", ".123", "-1;", "2.52181e-07", "5.30781e-06",
	};

	for (int i = 0; i < sizeof(bufs) / sizeof(bufs[0]); i++) {
		printf("strtod(\"%s\") = %.10lf", bufs[i],
		       strtod(bufs[i], &buf));
		printf("\t%s\n", buf);
	}

	for (int i = 1; i < argc; i++) {
		printf("strtod(\"%s\") = %.10lf", argv[i],
		       strtod(argv[i], &buf));
		printf("\t%s\n", buf);
	}

	return 0;
}
