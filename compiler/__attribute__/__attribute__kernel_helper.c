#include <stdio.h>

int bpf_probe_read (void *dst, int size, const void *unsafe_ptr)
	__attribute__((kernel_helper(4)));

int main(void)
{
	return 0;
}
