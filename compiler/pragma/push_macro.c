#include <stdio.h>

#define X 1
#pragma push_macro("X")
#undef X
#define X -1
#pragma pop_macro("X")

int main(void)
{
	printf("%d\n", X);
	return 0;
}
