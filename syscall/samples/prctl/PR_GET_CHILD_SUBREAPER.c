#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/prctl.h>

int main(void)
{
	int err, subreaper;
	err = prctl(PR_GET_CHILD_SUBREAPER, (int *)&subreaper);
	printf("err %d, subreaper %d\n", err, subreaper);

	return 0;
}
