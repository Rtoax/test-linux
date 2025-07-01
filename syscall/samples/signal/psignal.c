#include <signal.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	psignal(SIGXCPU, "SIGXCPU");
	psignal(SIGFPE, "SIGFPE");
	psignal(SIGSEGV, "SIGSEGV");
	psignal(SIGTRAP, "SIGTRAP");

	return 0;
}
