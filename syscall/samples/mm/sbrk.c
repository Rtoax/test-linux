#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(void)
{
	char *pmem;
	int i;
	void *sbrkret;

	pmem = (char *)malloc(32);
	if (pmem == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	printf("pmem = %p\n", pmem);

	sbrkret = sbrk(0);
	if (sbrkret != (void *)-1)
		printf("heap size on each load: %lu\n",
		       (long)sbrkret - (long)pmem);

	for (i = 0; i < 8; i++) {
		printf("sbrkret = %p\n", sbrk(1));
	}
	free(pmem);

	return 0;
}
