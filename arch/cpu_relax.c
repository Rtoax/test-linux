#if defined(__aarch64__)
#include "aarch64/asm/cpu_relax.h"
#elif defined(__x86_64__)
#include "x86_64/asm/cpu_relax.h"
#elif defined(__sw_64__)
#include "sw_64/asm/cpu_relax.h"
#endif

int main(void)
{
	cpu_relax();
	return 0;
}
