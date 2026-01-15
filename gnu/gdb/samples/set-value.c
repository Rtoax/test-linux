/**
 * gcc -O3 -ggdb
 */
#include <stdio.h>

static int alloc(void)
{
	return 0;
}

int __attribute__((optimize("-O0"))) main(void)
{
#ifdef VOLATILE_RC
	volatile
#endif
	int rc = 0;

	rc = alloc();
#ifdef GIVE_ME_SOME_INSN
	printf("alloc rc = %d\n", rc);
#endif
	if (rc != 0) {
		printf("Failed.\n");
		goto out;
	}

	printf("Success.\n");
out:
	return 1;
}
