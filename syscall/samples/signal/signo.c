#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(void)
{
#define NR_SIG(nr)	printf("%30s (%4d) : %s\n", #nr, nr, strsignal(nr));
#include "sig.h"
#undef NR_SIG

	return 0;
}
