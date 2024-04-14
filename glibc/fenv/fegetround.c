#include <fenv.h>
#include <stdio.h>
#include <math.h>

#define _print(val) printf("%s:%x\n", #val, val)

int main(void)
{
	_print(FE_TONEAREST);
	_print(FE_UPWARD);
	_print(FE_DOWNWARD);
	_print(FE_TOWARDZERO);

	float f = sqrtf(-1);

	fesetround(FE_DOWNWARD | FE_TONEAREST | FE_TOWARDZERO | FE_UPWARD);
	printf("%x\n", fegetround());

	return 0;
}
