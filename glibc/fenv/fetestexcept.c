#include <fenv.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
	double f;
	int raised;
	feclearexcept (FE_ALL_EXCEPT);

	f = sqrtf(-1);

	raised = fetestexcept (FE_OVERFLOW | FE_INVALID | FE_UNDERFLOW);
	if (raised & FE_OVERFLOW)
		printf("FE_OVERFLOW\n");
	if (raised & FE_INVALID)
		printf("FE_INVALID\n");
	if (raised & FE_UNDERFLOW)
		printf("FE_UNDERFLOW\n");

	return 0;
}
