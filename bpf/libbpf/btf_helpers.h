#pragma once

#define SYSFS_VMLINUX	"/sys/kernel/btf/vmlinux"

/**
 * bpftool btf dump generated vmlinux.h will not contains kfuncs if pahole
 * version less than v1.26 and kernel must newer than v6.10.
 *
 * linux commit ebb79e96f1ea ("kbuild: bpf: Tell pahole to DECL_TAG kfuncs")
 * v6.10-rc2-724-gebb79e96f1ea [0]
 * pahole commit 72e88f29c6f7 ("pahole: Inject kfunc decl tags into BTF")
 * v1.26-34-g72e88f29c6f7 [1]
 *
 * see bpftool:src/btf.c
 * [0] https://lore.kernel.org/all/324aac5c627bddb80d9968c30df6382846994cc8.1718207789.git.dxu@dxuuu.xyz/
 * [1] https://git.kernel.org/pub/scm/devel/pahole/pahole.git/commit/?id=72e88f29c6f7e14201756e65bd66157427a61aaf
 * [2] https://lore.kernel.org/all/cover.1718207789.git.dxu@dxuuu.xyz/
 */
#ifdef BPF_NO_KFUNC_PROTOTYPES
#pragma message "Defined BPF_NO_KFUNC_PROTOTYPES"
extern struct task_struct *bpf_task_from_pid(s32 pid) __weak __ksym;
extern void bpf_task_release(struct task_struct *p) __weak __ksym;
/* Add more kfuncs here */
#endif

const char *btf_kind_name(int kind);

int btf_has_ksym(const char *ksym);
int btf_has_kfunc(const char *kfunc);
int btf_has_decl_tag(const char *ksym);
