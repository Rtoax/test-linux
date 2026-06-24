/**
 * int bpf_strnlen(const char *s__ign, size_t count);
 *
 * - https://docs.ebpf.io/linux/kfuncs/bpf_strnlen/
 */
#include "vmlinux.h"

void test(void)
{
	bpf_strnlen("abc", 2);
}
