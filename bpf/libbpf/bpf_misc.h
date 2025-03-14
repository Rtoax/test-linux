#pragma once
#if defined(__TARGET_ARCH_x86)
#define SYSCALL_WRAPPER 1
#define SYS_PREFIX "__x64_"
#elif defined(__TARGET_ARCH_arm64)
#define SYSCALL_WRAPPER 1
#define SYS_PREFIX "__arm64_"
#else
#error Not support arch or not define __TARGET_ARCH_
#endif

/**
 * Kernel commit 1e33759c788c ("bpf, trace: add BPF_F_CURRENT_CPU flag for
 * bpf_perf_event_output") introduce definitions. v4.6-rc2-1065-g1e33759c788c
 */
#ifndef BPF_F_INDEX_MASK
#define BPF_F_INDEX_MASK	0xffffffffULL
#endif
#ifndef BPF_F_CURRENT_CPU
#define BPF_F_CURRENT_CPU	BPF_F_INDEX_MASK
#endif

/**
 * Kernel commit 457f44363a88 ("bpf: Implement BPF ring buffer and verifier
 * support for it") v5.7-rc7-2894-g457f44363a88
 */
#ifndef BPF_MAP_TYPE_RINGBUF
#define BPF_MAP_TYPE_RINGBUF	0x1b
#endif

/**
 * kernel commit 3274f52073d8 (bpf: add 'flags' attribute to BPF_MAP_UPDATE_ELEM
 * command") v3.18-rc4-938-g3274f52073d8
 */
#ifndef BPF_NOEXIST
#define BPF_NOEXIST	1 /* create new element if it didn't exist */
#endif

/**
 * kernel commit 6c9059817432 ("bpf: pre-allocate hash map elements")
 * v4.5-rc7-1214-g6c9059817432
 */
#ifndef BPF_F_NO_PREALLOC
#define BPF_F_NO_PREALLOC	(1U << 0)
#endif

/**
 * kernel commit 281920b7e0b3 ("bpf: Devmap adjust uapi for attach bpf program")
 * v5.7-7182-g281920b7e0b3 move struct bpf_devmap_val {} to uapi.
 */
#if KVERSION < 5 || (KVERSION == 5 && KPATCHLEVEL < 7)
struct bpf_devmap_val {
	__u32 ifindex;   /* device index */
	union {
		int   fd;  /* prog fd on map write */
		__u32 id;  /* prog id on map read */
	} bpf_prog;
};
#endif

/**
 * kernel commit 644bfe51fa49 ("cpumap: Formalize map value as a named struct")
 * v5.8-rc4-1448-g644bfe51fa49 introduce struct bpf_cpumap_val {} to uapi.
 */
#if KVERSION < 5 || (KVERSION == 5 && KPATCHLEVEL < 8)
struct bpf_cpumap_val {
	__u32 qsize;    /* queue size to remote target CPU */
	/**
	 * kernel commit 9216477449f3 ("bpf: cpumap: Add the possibility to
	 * attach an eBPF program to cpumap") v5.8-rc4-1449-g9216477449f3
	 */
	union {
		int   fd;       /* prog fd on map write */
		__u32 id;       /* prog id on map read */
	};
};
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
