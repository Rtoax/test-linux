#include <stdio.h>

#if 0
#define kernel_helper __attribute__((kernel_helper(4)))
#else
#define kernel_helper
#endif

int bpf_probe_read (void *dst, int size, const void *unsafe_ptr)
	kernel_helper;

int main(void)
{
	return 0;
}
