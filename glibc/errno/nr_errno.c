#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(void)
{
#define NR_ERRNO(no) printf("%30s (%4d)(-0x%x) : %s\n", #no, no, -no, strerror(no));
#include "nr_errno.h"
#undef NR_ERRNO

	printf("errno = %d\n", errno);
	printf("errno addr = 0x%lx\n", (unsigned long)&errno);

	return 0;
}
