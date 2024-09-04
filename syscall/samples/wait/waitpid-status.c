#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void print_wstatus(int status)
{
	printf("WIFEXITED(%d=0x%x)	= %d\n", status, status, WIFEXITED(status));
	printf("WEXITSTATUS(%d=0x%x)	= %d\n", status, status, WEXITSTATUS(status));
	printf("WTERMSIG(%d=0x%x)	= %d\n", status, status, WTERMSIG(status));
	printf("WSTOPSIG(%d=0x%x)	= %d\n", status, status, WSTOPSIG(status));
	printf("WIFSIGNALED(%d=0x%x)	= %d\n", status, status, WIFSIGNALED(status));
	printf("WIFSTOPPED(%d=0x%x)	= %d\n", status, status, WIFSTOPPED(status));
}

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
