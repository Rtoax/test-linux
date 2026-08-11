#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char buf[32] = { "1234567" };
	char buf2[32];

	memccpy(buf2, buf, '5', sizeof(buf));
	printf("%s\n", buf2);

	return 0;
}
