#include "relocation-truncated-to-fit.h"

__sbss int a;

int main(void)
{
	int b = a + a;

	return b;
}
