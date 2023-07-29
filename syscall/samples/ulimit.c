#include <stdio.h>
#include <ulimit.h>
#include <errno.h>
#include <string.h>
#include <sys/vlimit.h>


int main(void)
{
	int fsize = ulimit(UL_GETFSIZE);
	/* These system calls always return -1 and set errno to ENOSYS */
	if (fsize == -1) {
		fprintf(stderr, "ulimit: %s\n", strerror(ENOSYS));
	}

	return 0;
}
