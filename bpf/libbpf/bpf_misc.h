#pragma once
#if defined(__TARGET_ARCH_x86)
#define SYSCALL_WRAPPER 1
#define SYS_PREFIX "__x64_"
#elif defined(__TARGET_ARCH_arm64)
#define SYSCALL_WRAPPER 1
#define SYS_PREFIX "__arm64_"
#else
#error Not support arch
#endif

/**
 * FIXME: Why couldn't use __builtin_strcmp/__builtin_strlen ?
 */
static __always_inline bool str_eq(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++) {
		if (a[i] != b[i])
			return false;
		if (a[i] == '\0')
			break;
	}
	return true;
}

static __always_inline int str_len(char *s, int max_len)
{
	for (int i = 0; i < max_len; i++) {
		if (s[i] == '\0')
			return i;
	}
	if (s[max_len - 1] != '\0')
		return max_len;
	return 0;
}
