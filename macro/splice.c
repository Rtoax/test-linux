#include <stdio.h>

#define XcuX(a, b) a##hip##b

#define make_cuFloatComplex XcuX(make_, FloatComplex)

void make_cuFloatComplex(void)
{
	printf("%s\n", __func__);
}

int main(void)
{
	make_cuFloatComplex();
	return 0;
}
