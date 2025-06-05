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
#include "bpf_helpers.h"


#define EPERM  1

/**
 * See lsm_hook_defs.h
 */
#if CONFIG_BPF_SYSCALL == y && defined(LSM_BPF)
# pragma message "Compile lsm/bpf"
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
# pragma message "Compile lsm/socket_create"
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
#elif defined(LSM_SOCKET_SENDMSG)
# pragma message "Compile lsm/socket_sendmsg"
/**
 * LSM_HOOK(int, 0, socket_sendmsg, struct socket *sock, struct msghdr *msg,
 *	    int size);
 */
SEC("lsm/socket_sendmsg")
int BPF_PROG(socket_sendmsg, struct socket *sock, struct msghdr *msg, int size,
	     int ret)
{
	bpf_printk("LSM: socket_sendmsg() worked, ret %d", ret);
	/**
	 * If return -EPERM, all process use TCP will running failed, thus,
	 * just return 0 here.
	 */
	return 0;
}
#elif defined(LSM_FILE_OPEN)
# pragma message "Compile lsm/file_open"
/**
 * see also linux:tools/testing/selftests/bpf/progs/verifier_vfs_accept.c
 */
SEC("lsm/file_open")
int BPF_PROG(file_open, struct file *file)
{
	char buf[128] = "N/A";
	char exe[128] = "N/A";
#if defined(SUPPORT_BPF_PATH_D_PATH)
# pragma message "lsm/file_open: support bpf_path_d_path()"
	struct path *path = &file->f_path;
	bpf_path_d_path(path, buf, sizeof(buf));
#endif
#if defined(SUPPORT_BPF_GET_TASK_EXE_FILE)
# pragma message "lsm/file_open: support bpf_get_task_exe_file()"
	struct file *acquired;
	acquired = bpf_get_task_exe_file(bpf_get_current_task_btf());
	if (acquired) {
		struct path *path_exe = &acquired->f_path;
		bpf_path_d_path(path_exe, exe, sizeof(exe));
		bpf_put_file(acquired);
	}
#endif
	bpf_printk("LSM: file_open(%s) exe=%s\n", buf, exe);
	return 0;
}
#else
# error "Not found any lsm prog"
#endif

char LICENSE[] SEC("license") = "GPL";
