#include <stdio.h>
#include <fenv.h>

int main(void)
{
	fenv_t envp;
	fegetenv(&envp);

	/* TODO: how to print fenv_t */

	return 0;
}
