
#include <stdio.h>
#include <string.h>
#include <signal.h>


int main(void)
{
	printf("SIGXCPU = %d, %s\n", SIGXCPU, strsignal(SIGXCPU));
	printf("SIGFPE = %d, %s\n", SIGFPE, strsignal(SIGFPE));
	printf("SIGSEGV = %d, %s\n", SIGSEGV, strsignal(SIGSEGV));
	printf("SIGTRAP = %d, %s\n", SIGTRAP, strsignal(SIGTRAP));

	return 0;
}
