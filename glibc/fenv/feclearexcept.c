#include <fenv.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	feclearexcept(FE_INEXACT | FE_DIVBYZERO);
	return 0;
}
