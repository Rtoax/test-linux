/**
 * BPF_PROG_TYPE_STRUCT_OPS
 * BPF_MAP_TYPE_STRUCT_OPS
 *
 * This program types allows for the implementation of certain kernel features
 * in BPF.
 *
 * The kernel uses the "struct ops" pattern in C to implement interfaces. The
 * kernel defines a struct with function pointers as field types. An
 * implementation can create an instance of this struct and provide pointers to
 * its own functions that implement the signatures.
 *
 * This program type allows for the creation of these struct implementations
 * with BPF so locations in the kernel that allow it can BPF to implement the
 * functionality. For example the TCP congestion control algorithm.
 *
 * - linux < v6.7
 *   kernel/bpf/bpf_struct_ops_types.h
 *   BPF_STRUCT_OPS_TYPE(tcp_congestion_ops)
 * - linux > v6.7
 *   kernel/bpf/btf.c
 *   register_bpf_struct_ops()/__register_bpf_struct_ops()
 *
 * [1] https://lwn.net/Articles/809092/
 * [2] https://docs.ebpf.io/linux/program-type/BPF_PROG_TYPE_STRUCT_OPS/
 * [3] https://www.ebpf.top/post/ebpf_struct_ops/
 * [4] linux commit f6be98d19985 ("bpf, net: switch to dynamic registration")
 */

/**
 * TODO
 */
