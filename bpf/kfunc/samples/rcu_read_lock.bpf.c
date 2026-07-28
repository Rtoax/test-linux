/**
 * linux commit 9bb00b2895cb ("bpf: Add kfunc bpf_rcu_read_lock/unlock()")
 * v6.1-rc4-1167-g9bb00b2895cb
 *
 * Refs:
 * - https://docs.ebpf.io/linux/kfuncs/bpf_rcu_read_lock/
 */
#include "vmlinux.h"

extern void bpf_rcu_read_lock(void) __weak __ksym;
extern void bpf_rcu_read_unlock(void) __weak __ksym;

void test(void)
{
	bpf_rcu_read_lock();
	bpf_rcu_read_unlock();
}
