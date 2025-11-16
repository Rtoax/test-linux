#pragma once
#include <bpf/bpf_tracing.h>


/**
 * use bpf_strncmp() first
 */
static __always_inline bool str_eq(const char *a, const char *b, int len)
{
#if defined(SUPPORT_BPF_STRNCMP)
	return !bpf_strncmp(a, len, b);
#else
	int i;
	for (i = 0; i < len; i++) {
		if (a[i] != b[i])
			return false;
		if (a[i] == '\0')
			break;
	}
	return true;
#endif
}

/**
 * FIXME: Use __builtin_strlen() instead?
 */
static __always_inline int str_len(char *s, int max_len)
{
	int i;
	for (i = 0; i < max_len; i++) {
		if (s[i] == '\0')
			return i;
	}
	if (s[max_len - 1] != '\0')
		return max_len;
	return 0;
}

/**
 * TODO: why failed???????
 */
void __bpf_str_append(char *dst__ign, size_t dst_sz, const char *src__ign, size_t src_sz)
{
	dst__ign[0] = 'A';
	int i, j;

	for (i = 0; i < dst_sz && dst__ign[i] != '\0'; i++);

	dst__ign[0] = 'B';

	for (j = 0; i < dst_sz && j < src_sz && src__ign[j] != '\0'; j++, i++);
		//dst__ign[i++] = src__ign[j];

	dst__ign[0] = 'C';
#if 0
	if (i < dst_sz) {
		dst__ign[i] = '\0';
	} else {
		dst__ign[dst_sz - 1] = '\0';
	}
#endif
}
