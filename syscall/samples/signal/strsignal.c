#include <stdio.h>
#include <string.h>
#include <signal.h>


int main(void)
{
#define NR_SIG(nr)	printf("%30s : %s\n", #nr, strsignal(nr));
#include "sig.h"
#undef NR_SIG

	return 0;
}
