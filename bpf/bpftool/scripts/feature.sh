#!/bin/bash

sudo /usr/local/sbin/bpftool feature
# 我的环境 结果 3.10 内核 CentOS7
# Scanning system configuration...
# Unable to retrieve required privileges for bpf() syscall
# JIT compiler is enabled
# JIT compiler hardening is enabled for unprivileged users
# JIT compiler kallsyms exports are disabled
# Unable to retrieve global memory limit for JIT compiler for unprivileged users
# CONFIG_BPF is set to y
# CONFIG_BPF_SYSCALL is set to y
# CONFIG_HAVE_EBPF_JIT is set to y
# CONFIG_BPF_JIT is set to y
# CONFIG_BPF_JIT_ALWAYS_ON is set to y
# CONFIG_CGROUPS is set to y
# CONFIG_CGROUP_BPF is not set
# CONFIG_CGROUP_NET_CLASSID is not set
# CONFIG_SOCK_CGROUP_DATA is not set
# CONFIG_BPF_EVENTS is set to y
# CONFIG_KPROBE_EVENTS is not set
# CONFIG_UPROBE_EVENTS is not set
# CONFIG_TRACING is set to y
# CONFIG_FTRACE_SYSCALLS is set to y
# CONFIG_FUNCTION_ERROR_INJECTION is not set
# CONFIG_BPF_KPROBE_OVERRIDE is set to y
# CONFIG_NET is set to y
# CONFIG_XDP_SOCKETS is not set
# CONFIG_LWTUNNEL_BPF is not set
# CONFIG_NET_ACT_BPF is not set
# CONFIG_NET_CLS_BPF is set to m
# CONFIG_NET_CLS_ACT is set to y
# CONFIG_NET_SCH_INGRESS is set to m
# CONFIG_XFRM is set to y
# CONFIG_IP_ROUTE_CLASSID is set to y
# CONFIG_IPV6_SEG6_BPF is not set
# CONFIG_BPF_LIRC_MODE2 is not set
# CONFIG_BPF_STREAM_PARSER is not set
# CONFIG_NETFILTER_XT_MATCH_BPF is set to m
# CONFIG_BPFILTER is not set
# CONFIG_BPFILTER_UMH is not set
# CONFIG_TEST_BPF is not set
# CONFIG_HZ is set to 1000
# 
# Scanning system call availability...
# bpf() syscall is available
# 
# Scanning eBPF program types...
# eBPF program_type socket_filter is NOT available
# eBPF program_type kprobe is available
# eBPF program_type sched_cls is NOT available
# eBPF program_type sched_act is NOT available
# eBPF program_type tracepoint is available
# eBPF program_type xdp is NOT available
# eBPF program_type perf_event is available
# eBPF program_type cgroup_skb is NOT available
# eBPF program_type cgroup_sock is NOT available
# eBPF program_type lwt_in is NOT available
# eBPF program_type lwt_out is NOT available
# eBPF program_type lwt_xmit is NOT available
# eBPF program_type sock_ops is NOT available
# eBPF program_type sk_skb is NOT available
# eBPF program_type cgroup_device is NOT available
# eBPF program_type sk_msg is NOT available
# eBPF program_type raw_tracepoint is NOT available
# eBPF program_type cgroup_sock_addr is NOT available
# eBPF program_type lwt_seg6local is NOT available
# eBPF program_type lirc_mode2 is NOT available
# eBPF program_type sk_reuseport is NOT available
# eBPF program_type flow_dissector is NOT available
# eBPF program_type cgroup_sysctl is NOT available
# eBPF program_type raw_tracepoint_writable is NOT available
# eBPF program_type cgroup_sockopt is NOT available
# eBPF program_type tracing is NOT available
# eBPF program_type struct_ops is NOT available
# eBPF program_type ext is NOT available
# eBPF program_type lsm is NOT available
# eBPF program_type sk_lookup is NOT available
# 
# Scanning eBPF map types...
# eBPF map_type hash is available
# eBPF map_type array is available
# eBPF map_type prog_array is available
# eBPF map_type perf_event_array is available
# eBPF map_type percpu_hash is available
# eBPF map_type percpu_array is available
# eBPF map_type stack_trace is available
# eBPF map_type cgroup_array is NOT available
# eBPF map_type lru_hash is available
# eBPF map_type lru_percpu_hash is available
# eBPF map_type lpm_trie is available
# eBPF map_type array_of_maps is available
# eBPF map_type hash_of_maps is available
# eBPF map_type devmap is available
# eBPF map_type sockmap is NOT available
# eBPF map_type cpumap is NOT available
# eBPF map_type xskmap is NOT available
# eBPF map_type sockhash is NOT available
# eBPF map_type cgroup_storage is NOT available
# eBPF map_type reuseport_sockarray is NOT available
# eBPF map_type percpu_cgroup_storage is NOT available
# eBPF map_type queue is NOT available
# eBPF map_type stack is NOT available
# eBPF map_type sk_storage is NOT available
# eBPF map_type devmap_hash is NOT available
# eBPF map_type struct_ops is NOT available
# eBPF map_type ringbuf is NOT available
# eBPF map_type inode_storage is NOT available
# 
# Scanning eBPF helper functions...
# eBPF helpers supported for program type socket_filter:
# eBPF helpers supported for program type kprobe:
# 	- bpf_map_lookup_elem
# 	- bpf_map_update_elem
# 	- bpf_map_delete_elem
# 	- bpf_probe_read
# 	- bpf_ktime_get_ns
# 	- bpf_get_prandom_u32
# 	- bpf_get_smp_processor_id
# 	- bpf_tail_call
# 	- bpf_get_current_pid_tgid
# 	- bpf_get_current_uid_gid
# 	- bpf_get_current_comm
# 	- bpf_perf_event_read
# 	- bpf_perf_event_output
# 	- bpf_get_stackid
# 	- bpf_get_current_task
# 	- bpf_get_numa_node_id
# 	- bpf_probe_read_str
# 	- bpf_perf_event_read_value
# 	- bpf_override_return
# 	- bpf_get_stack
# eBPF helpers supported for program type sched_cls:
# eBPF helpers supported for program type sched_act:
# eBPF helpers supported for program type tracepoint:
# 	- bpf_map_lookup_elem
# 	- bpf_map_update_elem
# 	- bpf_map_delete_elem
# 	- bpf_probe_read
# 	- bpf_ktime_get_ns
# 	- bpf_get_prandom_u32
# 	- bpf_get_smp_processor_id
# 	- bpf_tail_call
# 	- bpf_get_current_pid_tgid
# 	- bpf_get_current_uid_gid
# 	- bpf_get_current_comm
# 	- bpf_perf_event_read
# 	- bpf_perf_event_output
# 	- bpf_get_stackid
# 	- bpf_get_current_task
# 	- bpf_get_numa_node_id
# 	- bpf_probe_read_str
# 	- bpf_get_stack
# eBPF helpers supported for program type xdp:
# eBPF helpers supported for program type perf_event:
# 	- bpf_map_lookup_elem
# 	- bpf_map_update_elem
# 	- bpf_map_delete_elem
# 	- bpf_probe_read
# 	- bpf_ktime_get_ns
# 	- bpf_get_prandom_u32
# 	- bpf_get_smp_processor_id
# 	- bpf_tail_call
# 	- bpf_get_current_pid_tgid
# 	- bpf_get_current_uid_gid
# 	- bpf_get_current_comm
# 	- bpf_perf_event_read
# 	- bpf_perf_event_output
# 	- bpf_get_stackid
# 	- bpf_get_current_task
# 	- bpf_get_numa_node_id
# 	- bpf_probe_read_str
# 	- bpf_perf_prog_read_value
# 	- bpf_get_stack
# eBPF helpers supported for program type cgroup_skb:
# eBPF helpers supported for program type cgroup_sock:
# eBPF helpers supported for program type lwt_in:
# eBPF helpers supported for program type lwt_out:
# eBPF helpers supported for program type lwt_xmit:
# eBPF helpers supported for program type sock_ops:
# eBPF helpers supported for program type sk_skb:
# eBPF helpers supported for program type cgroup_device:
# eBPF helpers supported for program type sk_msg:
# eBPF helpers supported for program type raw_tracepoint:
# eBPF helpers supported for program type cgroup_sock_addr:
# eBPF helpers supported for program type lwt_seg6local:
# eBPF helpers supported for program type lirc_mode2:
# eBPF helpers supported for program type sk_reuseport:
# eBPF helpers supported for program type flow_dissector:
# eBPF helpers supported for program type cgroup_sysctl:
# eBPF helpers supported for program type raw_tracepoint_writable:
# eBPF helpers supported for program type cgroup_sockopt:
# eBPF helpers supported for program type tracing:
# eBPF helpers supported for program type struct_ops:
# eBPF helpers supported for program type ext:
# eBPF helpers supported for program type lsm:
# eBPF helpers supported for program type sk_lookup:
# 
# Scanning miscellaneous eBPF features...
# Large program size limit is NOT available
# 
