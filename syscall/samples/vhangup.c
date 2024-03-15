#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int ret = vhangup();
	if (ret == -1) {
		fprintf(stderr, "vhangup %m\n");
		return -errno;
	}
	return 0;
}


