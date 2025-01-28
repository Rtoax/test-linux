#include <stdio.h>
#include <fcntl.h>

int main(void)
{
#define O_FLAG(f) printf("%-32s : %08o (%08x)\n", #f, f, f);
#include "O_.h"
	return 0;
}
