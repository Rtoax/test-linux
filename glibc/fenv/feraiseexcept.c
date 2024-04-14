#include <fenv.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
	int flag = 99;

	flag = fetestexcept(FE_INEXACT);
	printf("%d\n", flag);

	flag = feraiseexcept(FE_INEXACT | FE_DIVBYZERO);
	printf("%d\n", flag);

	return 0;
}
