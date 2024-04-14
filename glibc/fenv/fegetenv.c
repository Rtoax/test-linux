#include <stdio.h>
#include <math.h>
#include <fenv.h>


int main(void)
{
	fenv_t envp;

	fegetenv(&envp);
	printf("envp = %x\n", envp);

	return 0;
}

