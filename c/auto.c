#include "unused.h"

int main(void)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-int"
	auto __unused i1 = 10;
#pragma GCC diagnostic pop
	auto __unused int i2 = 10;
	return 0;
}
