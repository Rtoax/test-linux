#pragma once
#include <bpf/bpf_tracing.h>

static __always_inline bool str_eq(const char *a, const char *b, int len)
{
/**
 * use bpf_strncmp() first
 */
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

static __always_inline int strlen(char *s, int max_len)
{
#if defined(SUPPORT_BPF_STRNLEN)
	return bpf_strnlen(s, max_len);
#elif defined(SUPPORT_BPF_STRLEN)
	return bpf_strlen(s);
#else
	int i;
	for (i = 0; i < max_len; i++) {
		if (s[i] == '\0')
			return i;
	}
	if (s[max_len - 1] != '\0')
		return max_len;
	return 0;
#endif
}

/**
 * Append src string to dst string
 * see https://github.com/bpftrace/bpftrace/pull/4601
 */
static void __bpf_str_append(char *dst__ign, size_t dst_sz,
			     const char *src__ign, size_t src_sz)
{
	int i, j;
	int dst_len = strlen(dst__ign, dst_sz);
	int src_len = strlen(src__ign, src_sz);

	# pragma unroll
	for (i = dst_len, j = 0;
	     i < dst_sz && j < src_len && src__ign[j] != '\0'; j++, i++)
		dst__ign[i] = src__ign[j];
}
