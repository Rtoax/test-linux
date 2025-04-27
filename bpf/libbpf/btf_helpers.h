#pragma once

#define SYSFS_VMLINUX	"/sys/kernel/btf/vmlinux"

/* see bpftool:src/btf.c */
#ifdef BPF_NO_KFUNC_PROTOTYPES
#pragma message "Defined BPF_NO_KFUNC_PROTOTYPES"
extern struct task_struct *bpf_task_from_pid(s32 pid) __weak __ksym;
extern void bpf_task_release(struct task_struct *p) __weak __ksym;
#endif

int btf_has_ksym(const char *ksym);
int btf_has_kfunc(const char *kfunc);
int btf_has_decl_tag(const char *ksym);
