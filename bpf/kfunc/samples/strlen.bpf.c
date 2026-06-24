/**
 * int bpf_strlen(const char *s__ign);
 *
 * https://docs.ebpf.io/linux/kfuncs/bpf_strlen/
 */
#include "vmlinux.h"

void test(void)
{
	bpf_strlen("abc");
}
