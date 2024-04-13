#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	/* F_GETFD, F_SETFD */
	int stdoutno = fileno(stdout);
	int flagout = fcntl(stdoutno, F_GETFD, 0);
	int newno = fcntl(stdoutno, F_SETFD, flagout);

	printf("stdoutno = %d, flagout = %d, newno = %d\n", stdoutno, flagout, newno);

	return 0;
}
