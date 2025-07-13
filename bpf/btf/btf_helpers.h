// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#define SYSFS_VMLINUX	"/sys/kernel/btf/vmlinux"

#define MAX_NAME			96
#define MAX_STR				256
#define MAX_VALUES			6
#define MAX_ARGS			(MAX_VALUES - 1)

struct value {
	char name[MAX_STR];
	enum {
		ARG1, ARG2, ARG3, ARG4, ARG5, RETURN
	} base_arg;
	__u32 offset;
	__u32 size;
	__u64 type_id;
	__u64 flags;
	__u64 predicate_value;
};

struct func {
	char name[MAX_NAME];
	char mod[MAX_NAME];
	__s32 id;
	__u8 nr_args;
	__u64 ip;
	struct value args[MAX_VALUES];
};

#if defined(KAPI_NO_BPF_RB_ROOT) && defined(TEST_RBTREE)
struct bpf_rb_root {
	__u64 __opaque[2];
};

struct bpf_rb_node {
	__u64 __opaque[4];
};
#endif

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
/* https://github.com/Rtoax/linux/tree/p056-bpf_task_cwd */
extern int bpf_task_cwd_from_pid(pid_t pid, char *buf, u32 buf_len) __weak __ksym;
# ifdef TEST_RBTREE
extern int bpf_rbtree_add_impl(struct bpf_rb_root *root, struct bpf_rb_node *node, bool (*less)(struct bpf_rb_node *, const struct bpf_rb_node *), void *meta__ign, u64 off) __weak __ksym;
extern struct bpf_rb_node *bpf_rbtree_first(struct bpf_rb_root *root) __weak __ksym;
extern struct bpf_rb_node *bpf_rbtree_remove(struct bpf_rb_root *root, struct bpf_rb_node *node) __weak __ksym;
# endif
/* Add more kfuncs here */
#endif

const char *btf_kind_name(int kind);

int btf_has_ksym(const char *ksym);
int btf_has_kfunc(const char *kfunc);
int btf_has_decl_tag(const char *ksym);
