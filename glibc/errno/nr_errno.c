#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(void)
{
	int i, nr;

#define NR_ERRNO(no) printf("%30s (%4d)(-0x%x) : %s\n", #no, no, -no, strerror(no));
#include "nr_errno.h"
#undef NR_ERRNO

	printf("errno = %d\n", errno);
	printf("errno addr = 0x%lx\n", (unsigned long)&errno);
	printf("ELIBMAX = %d\n", ELIBMAX);

	for (i = 0, nr = 0; i < 256; i++) {
		if (strerror(i) != NULL &&
		    strncmp(strerror(i), "Unknown error", 13) != 0)
			nr++;
	}
	printf("max nr %d\n", nr);

	return 0;
}
