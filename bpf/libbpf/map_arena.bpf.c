/**
 * BPF_MAP_TYPE_ARENA
 *
 * bpf_arena is a sparse shared memory region between the bpf program and user
 * space.
 *
 * - linux >= v6.9 commit 317460317a02 ("bpf: Introduce bpf_arena.")
 */
#include "vmlinux.h"
#include <linux/version.h>
#include <bpf/bpf_helpers.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0)
/* TODO */
#else
#warning "only kernel >= v6.9 support BPF_MAP_TYPE_ARENA"
#endif

char _license[] SEC("license") = "GPL";
