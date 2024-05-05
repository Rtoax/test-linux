#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <errno.h>
#include <string.h>

struct test_struct {
	int id;
};

void print_mstatus(enum mcheck_status mstatus)
{
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
	default:
		printf("Memory is OK.\n");
		break;
	}
}

void abortfun(enum mcheck_status mstatus)
{
	fprintf(stderr, "abortfun called with %d\n", mstatus);
	print_mstatus(mstatus);
}

int main(int argc, char *argv[])
{
	struct test_struct *p1 = NULL, *p2 = NULL, *tmpp;

	if (mcheck_pedantic(abortfun) != 0) {
		fprintf(stderr, "mcheck:%s\n", strerror(errno));
		return -1;
	}
	p1 = malloc(sizeof(struct test_struct)*10);
	p2 = malloc(sizeof(struct test_struct)*10);

	tmpp = p1 - 1;	/* overflow */
	tmpp[0].id = 10;
	tmpp = p2 - 1;	/* overflow */
	tmpp[0].id = 10;

	mcheck_check_all();

	free(p1);
	free(p2);
	return 0;
}

