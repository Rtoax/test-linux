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

static __always_inline size_t strlen(const char *s, size_t max_len)
{
#if defined(SUPPORT_BPF_STRNLEN)
	return bpf_strnlen(s, max_len);
#elif defined(SUPPORT_BPF_STRLEN)
	return bpf_strlen(s);
#else
	size_t i;
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
 *
 * return the append bytes size.
 */
static size_t __bpf_str_append(char *dst__ign, size_t dst_sz,
			       const char *src__ign)
{
	__u8 i, j;
	size_t dst_len = strlen(dst__ign, dst_sz);

	for (i = dst_len, j = 0; i < dst_sz - 1 && src__ign[j] != '\0';
	     j++, i++)
		dst__ign[i] = src__ign[j];

	dst__ign[i] = '\0';

	return j;
}

/**
 * Prepend src string in front of dst string
 * see https://github.com/bpftrace/bpftrace/pull/4601
 *
 * return the prepend bytes size.
 */
static size_t __bpf_str_prepend(char *dst__ign, size_t dst_sz,
				const char *src__ign, size_t src_sz)
{
	__u8 i;
	const __u8 dst_len = strlen(dst__ign, dst_sz);
	const __u8 src_len = strlen(src__ign, src_sz);

	if (dst_len + src_len > dst_sz - 1) {
		return 0;
	}

	for (i = 0; i < dst_len && dst__ign[i] != '\0'; i++) {
		__u8 idx = dst_len - i - 1;
		dst__ign[src_len + idx] = dst__ign[idx];
	}
	dst__ign[src_len + dst_len] = '\0';

	for (i = 0; i < src_len && i < dst_sz && src__ign[i] != '\0'; i++) {
		dst__ign[i] = src__ign[i];
	}

	return src_len;
}
