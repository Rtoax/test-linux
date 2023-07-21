#include <signal.h>
#include <stdio.h>
#include <string.h>

int main()
{
	psignal(SIGXCPU, "SIGXCPU");
	psignal(SIGFPE, "SIGFPE");
	psignal(SIGSEGV, "SIGSEGV");
	psignal(SIGTRAP, "SIGTRAP");

	return 0;
}
