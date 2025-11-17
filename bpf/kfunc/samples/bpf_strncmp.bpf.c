/**
 * long bpf_strncmp(const char *s1, u32 s1_sz, const char *s2);
 */
#include "vmlinux.h"

void test(void)
{
	char s1[] = "abc";
	char s2[] = "123";
	bpf_strncmp(s1, 3, s2);
}
