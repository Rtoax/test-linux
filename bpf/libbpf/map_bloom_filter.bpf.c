/**
 * BPF_MAP_TYPE_BLOOM_FILTER
 *
 * Bloom filters are a space-efficient probabilistic data structure used to
 * quickly test whether an element exists in a set. In a bloom filter, false
 * positives are possible whereas false negatives are not.
 *
 * (布隆过滤器是一种节省空间的概率数据结构，用于快速测试集合中是否存在某个元素。
 * 在布隆过滤器中，可能会出现误报，但不会出现漏报。)
 *
 * - linux >= v5.15 commit 9330986c0300 ("bpf: Add bloom filter map implementation")
 */
#include "vmlinux.h"
#include <linux/version.h>
#include <bpf/bpf_helpers.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 15, 0)
struct map_bloom_type {
	__uint(type, BPF_MAP_TYPE_BLOOM_FILTER);
	__type(value, __u32);
	__uint(max_entries, 10000);
	__uint(map_extra, 5);
} map_bloom SEC(".maps");
#else
#warning "only kernel >= v5.15 support BPF_MAP_TYPE_BLOOM_FILTER"
#endif

char _license[] SEC("license") = "GPL";
