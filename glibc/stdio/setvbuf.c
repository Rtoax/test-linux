#include <stdio.h>

int main(void)
{
	int i;
	char string[256] = {"I love you, Yuehua Xue!"};
	char outbuf[BUFSIZ];

	setbuf(stdout, outbuf);
	setvbuf(stdout, outbuf, _IOFBF, sizeof(string));
	setbuffer(stdout, outbuf, sizeof(string));
	setlinebuf(stdout);

	fflush(stdout);

	for (i = 0; i < 32; i++)
		fprintf(stdout, "Rong Tao \033[1;5;31m❤\033[m %s\n", "Xue Yuehua");

	printf("%s\n", string);

	return 0;
}
