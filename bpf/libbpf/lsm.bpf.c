/**
 * BPF_PROG_TYPE_LSM
 *
 * This eBPF programs can attach to LSM (Linux Security Module) hooks. These
 * are the same hooks as used by programs such as SELinux and AppArmor.
 *
 * The primary use case is to implement security software. For example, the
 * socket_create hook is called when a process calls the socket syscall, if
 * the eBPF program returns 0 the socket is allowed to be created, but the
 * eBPF program can also return an error value to block the socket creation.
 *
 * The list of all LSM hooks can be found in: lsm_hook_defs.h [1], additional
 * documentation for these hooks lives in lsm_hooks.h [2].
 *
 * [1] https://github.com/torvalds/linux/blob/master/include/linux/lsm_hook_defs.h
 * [2] https://github.com/torvalds/linux/blob/master/include/linux/lsm_hooks.h
 */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>


#define EPERM  1

/**
 * See lsm_hook_defs.h
 */
#if CONFIG_BPF_SYSCALL == y && defined(LSM_BPF)
/**
 * LSM_HOOK(int, 0, bpf, int cmd, union bpf_attr *attr, unsigned int size)
 */
SEC("lsm/bpf")
int BPF_PROG(lsm_bpf, int cmd, union bpf_attr *attr, unsigned int size, int ret)
{
	/**
	 * ret is the return value from the previous BPF program or 0 if
	 * it's the first hook.
	 */
	if (ret != 0)
		return ret;

	bpf_printk("LSM: block bpf() worked");
	return -EPERM;
}
#elif defined(LSM_SOCKET_CREATE)
/**
 * LSM_HOOK(int, 0, socket_create, int family, int type, int protocol, int kern)
 */
SEC("lsm/socket_create")
int BPF_PROG(socket_create, int family, int type, int protocol, int kern,
	     int ret)
{
	/**
	 * ret is the return value from the previous BPF program
	 * or 0 if it's the first hook.
	 */
	if (ret != 0)
		return ret;

#if defined(UID)
# pragma message "lsm/socket_create only for current UID"
	u64 uid;
	uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
	if (uid != UID)
		return 0;
#endif

	bpf_printk("LSM: block socket_create() worked");
	return -EPERM;
}
#endif

char LICENSE[] SEC("license") = "GPL";
