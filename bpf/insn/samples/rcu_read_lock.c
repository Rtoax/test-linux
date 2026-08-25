/**
 * extern void bpf_rcu_read_lock(void) __weak __ksym;
 * extern void bpf_rcu_read_unlock(void) __weak __ksym;
 *
 * linux commit 9bb00b2895cb ("bpf: Add kfunc bpf_rcu_read_lock/unlock()")
 * v6.1-rc4-1167-g9bb00b2895cb
 *
 * BPF_PROG_TYPE_CGROUP_DEVICE  v6.12 -
 * BPF_PROG_TYPE_CGROUP_SKB
 * BPF_PROG_TYPE_CGROUP_SOCK  v6.12 -
 * BPF_PROG_TYPE_CGROUP_SOCKOPT  v6.12 -
 * BPF_PROG_TYPE_CGROUP_SOCK_ADDR  v6.7 -
 * BPF_PROG_TYPE_CGROUP_SYSCTL  v6.12 -
 * BPF_PROG_TYPE_LSM
 * BPF_PROG_TYPE_LWT_IN
 * BPF_PROG_TYPE_LWT_OUT
 * BPF_PROG_TYPE_LWT_SEG6LOCAL
 * BPF_PROG_TYPE_LWT_XMIT
 * BPF_PROG_TYPE_NETFILTER
 * BPF_PROG_TYPE_PERF_EVENT  v6.12 -
 * BPF_PROG_TYPE_SCHED_ACT
 * BPF_PROG_TYPE_SCHED_CLS
 * BPF_PROG_TYPE_SK_SKB
 * BPF_PROG_TYPE_SOCKET_FILTER
 * BPF_PROG_TYPE_SOCK_OPS  v6.15 -
 * BPF_PROG_TYPE_STRUCT_OPS
 * BPF_PROG_TYPE_SYSCALL
 * BPF_PROG_TYPE_TRACEPOINT  v6.12 -
 * BPF_PROG_TYPE_TRACING
 * BPF_PROG_TYPE_XDP
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_rcu_read_lock/
 */
#include <stdio.h>
#include "bpf_insn_samples.h"
#include "bpf_insn.h"
#include "btf_helpers.h"

static struct bpf_insn insns_buf[1024];

BPF_INSN_SAMPLE_FUNC_PROTO(rcu_read_lock)
{
	int bpf_rcu_read_lock_id;
	int bpf_rcu_read_unlock_id;

	bpf_rcu_read_lock_id = btf_has_kfunc(NULL, "bpf_rcu_read_lock", true);
	bpf_rcu_read_unlock_id =
		btf_has_kfunc(NULL, "bpf_rcu_read_unlock", true);

	if (bpf_rcu_read_lock_id <= 0 || bpf_rcu_read_unlock_id <= 0) {
		fprintf(stderr, "ERROR: not found bpf_rcu_read_lock kfunc.\n");
		*cnt = 0;
		return NULL;
	}

	struct bpf_insn *insn = insns_buf;

	*insn++ = BPF_CALL_KFUNC(0, bpf_rcu_read_lock_id);
	*insn++ = BPF_CALL_KFUNC(0, bpf_rcu_read_unlock_id);
	*insn++ = BPF_MOV64_IMM(BPF_REG_0, 0);
	*insn++ = BPF_EXIT_INSN();

	*cnt = insn - insns_buf;
	return insns_buf;
}
