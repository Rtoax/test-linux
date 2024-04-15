#include <stdio.h>
#if __x86_x64__
# define MEMORY_BARRIER() __builtin_ia32_sfence()
#else
# define MEMORY_BARRIER() __sync_synchronize()
#endif

int main(void)
{
	MEMORY_BARRIER();
	return 0;
}
