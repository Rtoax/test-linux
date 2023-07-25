#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(void)
{
#define NR_ERRNO(no) printf("%30s (%4d) : %s\n", #no, no, strerror(no));
#include "nr_errno.h"
#undef NR_ERRNO

	return 0;
}
