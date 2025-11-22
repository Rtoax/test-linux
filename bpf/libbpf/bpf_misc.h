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
#if defined(XDP_DEVMAP) && !defined(HAVE_STRUCT_BPF_DEVMAP_VAL)
# if KVERSION < 5 || (KVERSION == 5 && KPATCHLEVEL < 7)
struct bpf_devmap_val {
	__u32 ifindex;   /* device index */
	union {
		int   fd;  /* prog fd on map write */
		__u32 id;  /* prog id on map read */
	} bpf_prog;
};
# endif
#endif

/**
 * kernel commit 644bfe51fa49 ("cpumap: Formalize map value as a named struct")
 * v5.8-rc4-1448-g644bfe51fa49 introduce struct bpf_cpumap_val {} to uapi.
 */
#ifdef XDP_CPUMAP
# if KVERSION < 5 || (KVERSION == 5 && KPATCHLEVEL < 8)
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
# endif
#endif

#if defined(KAPI_NO_BPF_RB_ROOT) && defined(TEST_RBTREE)
struct bpf_rb_root {
	__u64 __opaque[2];
};

struct bpf_rb_node {
	__u64 __opaque[4];
};
#endif

/**
 * bpftool btf dump generated vmlinux.h will not contains kfuncs if pahole
 * version less than v1.26 and kernel must newer than v6.10.
 *
 * linux commit ebb79e96f1ea ("kbuild: bpf: Tell pahole to DECL_TAG kfuncs")
 * v6.10-rc2-724-gebb79e96f1ea [0]
 * pahole commit 72e88f29c6f7 ("pahole: Inject kfunc decl tags into BTF")
 * v1.26-34-g72e88f29c6f7 [1]
 *
 * see bpftool:src/btf.c
 * [0] https://lore.kernel.org/all/324aac5c627bddb80d9968c30df6382846994cc8.1718207789.git.dxu@dxuuu.xyz/
 * [1] https://git.kernel.org/pub/scm/devel/pahole/pahole.git/commit/?id=72e88f29c6f7e14201756e65bd66157427a61aaf
 * [2] https://lore.kernel.org/all/cover.1718207789.git.dxu@dxuuu.xyz/
 */
#ifdef BPF_NO_KFUNC_PROTOTYPES
#pragma message "Defined BPF_NO_KFUNC_PROTOTYPES"
extern struct task_struct *bpf_task_from_pid(s32 pid) __weak __ksym;
extern void bpf_task_release(struct task_struct *p) __weak __ksym;
/* https://github.com/Rtoax/linux/tree/p056-bpf_task_cwd */
extern int bpf_task_cwd_from_pid(pid_t pid, char *buf, u32 buf_len) __weak __ksym;
# ifdef TEST_RBTREE
extern int bpf_rbtree_add_impl(struct bpf_rb_root *root, struct bpf_rb_node *node, bool (*less)(struct bpf_rb_node *, const struct bpf_rb_node *), void *meta__ign, u64 off) __weak __ksym;
extern struct bpf_rb_node *bpf_rbtree_first(struct bpf_rb_root *root) __weak __ksym;
extern struct bpf_rb_node *bpf_rbtree_remove(struct bpf_rb_root *root, struct bpf_rb_node *node) __weak __ksym;
# endif
/* Add more kfuncs here */
#endif

