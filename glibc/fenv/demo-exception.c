#include <fenv.h>
#include <stdio.h>
#include <math.h>

int execption_catch_handle(int raised)
{
	/* catch deal with */
	if (raised & FE_INEXACT)
		printf("FE_INEXACT\n");
	if (raised & FE_OVERFLOW)
		printf("FE_OVERFLOW\n");
	if (raised & FE_INVALID)
		printf("FE_INVALID\n");
	if (raised & FE_DIVBYZERO)
		printf("FE_DIVBYZERO\n");
	if (raised & FE_UNDERFLOW)
		printf("FE_UNDERFLOW\n");
	return 0;
}

int main(void)
{
	double f;
	int raised, i, j;
	fexcept_t exception;

	/* try */
	feclearexcept(FE_ALL_EXCEPT);

	/* throws */
	feraiseexcept(FE_DIVBYZERO);

	f = sqrtf(-1);

	fegetexceptflag(&exception, FE_INEXACT | FE_OVERFLOW | FE_INVALID | FE_DIVBYZERO | FE_UNDERFLOW);

	/* catch */
	raised = fetestexcept(exception);
	execption_catch_handle(raised);

	return 0;
}
