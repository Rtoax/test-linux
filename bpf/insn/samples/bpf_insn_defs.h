BPF_INSN_SAMPLE(perf_event_output)
BPF_INSN_SAMPLE(probe_read_kernel_str)
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
#ifdef SUPPORT_BPF_STRLEN
BPF_INSN_SAMPLE(strlen)
#endif
#ifdef SUPPORT_BPF_STRNLEN
BPF_INSN_SAMPLE(strnlen)
#endif
BPF_INSN_SAMPLE(send_signal)
BPF_INSN_SAMPLE(send_signal_thread)
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
/**
 * linux commit 9bb00b2895cb ("bpf: Add kfunc bpf_rcu_read_lock/unlock()")
 * v6.1-rc4-1167-g9bb00b2895cb
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 2, 0)
BPF_INSN_SAMPLE(rcu_read_lock)
#endif
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
