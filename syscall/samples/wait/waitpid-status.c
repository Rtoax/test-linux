#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "wait_helpers.h"

#ifdef TEST_MAIN_WAITPID_STATUS
int main(int argc, char *argv[])
{
	int status = 256;
	char *val;

	if (argc > 1) {
		val = argv[1];
		if (val[0] == '0' && val[1] == 'x')
			status = strtoul(val, NULL, 16);
		else
			status = atoi(argv[1]);
	}

	print_wstatus(status);

	return 0;
}
#endif
