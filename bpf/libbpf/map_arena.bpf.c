/**
 * BPF_MAP_TYPE_ARENA
 *
 * bpf_arena is a sparse shared memory region between the bpf program and user
 * space.
 *
 * - linux >= v6.9 commit 317460317a02 ("bpf: Introduce bpf_arena.")
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

/* TODO */

char _license[] SEC("license") = "GPL";
