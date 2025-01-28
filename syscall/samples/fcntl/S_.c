#include <stdio.h>
#include <fcntl.h>

int main(void)
{
#define S_MODE(m) printf("%-32s : %08o (%08x)\n", #m, m, m);
#include "S_.h"
	return 0;
}
