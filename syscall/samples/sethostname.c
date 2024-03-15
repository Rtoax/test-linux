#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int ret;

	ret = sethostname("localhost", 10);
	if (ret == -1) {
		fprintf(stderr, "sethostname %m\n");
		return -errno;
	}

	return 0;
}
