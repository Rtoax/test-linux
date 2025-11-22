BPF_INSN_SAMPLE(trace_printk)
BPF_INSN_SAMPLE(get_current_cgroup_id)
BPF_INSN_SAMPLE(get_current_task_btf)
/**
 * linux v5.16-rc4-1160-gc5fb19937455
 * commit c5fb19937455 ("bpf: Add bpf_strncmp helper")
 */
#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 16, 0)
BPF_INSN_SAMPLE(strncmp)
#endif
BPF_INSN_SAMPLE(strnstr)
/**
 * linux v5.15-12938-ge6f2dd0f8067
 * commit e6f2dd0f8067 ("bpf: Add bpf_loop helper")
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0)
BPF_INSN_SAMPLE(loop)
#endif
BPF_INSN_SAMPLE(cgroup_from_id)
BPF_INSN_SAMPLE(cgroup_acquire)
BPF_INSN_SAMPLE(task_from_pid)
BPF_INSN_SAMPLE(task_acquire)
/**
 * linux v6.0-11954-gc4bcfb38a95e
 * commit c4bcfb38a95e ("bpf: Implement cgroup storage available to non-cgroup-attached bpf progs")
 */
#if LINUX_VERSION_CODE > KERNEL_VERSION(6, 0, 0)
BPF_INSN_SAMPLE(cgrp_storage_get)
#endif
BPF_INSN_SAMPLE(get_func_ip)
BPF_INSN_SAMPLE(arena_alloc_pages)
BPF_INSN_SAMPLE(arena_reserve_pages)
BPF_INSN_SAMPLE(iter_task_vma_new)
