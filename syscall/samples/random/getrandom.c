#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/random.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int i;
	ssize_t ret;
	unsigned char buf[128];

	ret = getrandom(buf, sizeof(buf), GRND_NONBLOCK);

	for (i = 0; i < ret; i++)
		printf("%02x %c", buf[i], (i + 1) % 10 == 0 ? '\n' : '\0');
	printf("\n");

	return 0;
}
