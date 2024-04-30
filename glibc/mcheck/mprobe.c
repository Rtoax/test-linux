#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <errno.h>
#include <string.h>

void abortfun(enum mcheck_status mstatus)
{
	fprintf(stderr, "abortfun called with %d\n", mstatus);

	switch (mstatus) {
	case MCHECK_DISABLED:
		printf("consistency checking is not turned on\n");
		break;
	case MCHECK_OK:
		printf("block is fine\n");
		break;
	case MCHECK_FREE:
		printf("block freed twice\n");
		break;
	case MCHECK_HEAD:
		printf("memory before the block was clobbered\n");
		break;
	case MCHECK_TAIL:
		printf("memory after the block was clobbered\n");
		break;
	}
}

int main(int argc, char *argv[])
{
	char *p;
	enum mcheck_status mstatus;

	if (mcheck(abortfun) != 0) {
		fprintf(stderr, "mcheck:%s\n", strerror(errno));
		return -1;
	}
	p = malloc(10);
	mstatus = mprobe(p);
	printf("status:%d\n", mstatus);
	mstatus = mprobe(p + 1);
	printf("status:%d\n", mstatus);

#if 1
	free(p);
	printf("1st free finished.\n");
	free(p);
	printf("2nd free.\n");
#endif

	return 0;
}
