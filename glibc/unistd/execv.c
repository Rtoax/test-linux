#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(void)
{
	char *const argv [] = { "ls", "-a", NULL };

	execv("/bin/ls", argv);
	return 0;
}
