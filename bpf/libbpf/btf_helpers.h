#pragma once

#define SYSFS_VMLINUX	"/sys/kernel/btf/vmlinux"

/* see bpftool:src/btf.c */
#ifdef BPF_NO_KFUNC_PROTOTYPES
#pragma message "Defined BPF_NO_KFUNC_PROTOTYPES"
extern struct task_struct *bpf_task_from_pid(s32 pid) __weak __ksym;
extern void bpf_task_release(struct task_struct *p) __weak __ksym;
#endif

int btf_check_ksym_existence(const char *ksym_name);
int btf_check_kfunc_existence(const char *kfunc_name);
