// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#define SYSFS_VMLINUX "/sys/kernel/btf/vmlinux"

#define MAX_NAME 96
#define MAX_STR 256
#define MAX_VALUES 6
#define MAX_ARGS (MAX_VALUES - 1)
#define F_PTR 0x1 /* value is a pointer */

/**
 * if we can't get a type id for a type (such as module-specific type)
 * mark it as KSNOOP_ID_UNKNOWN since BTF lookup in bpf_snprintf_btf()
 * will fail and the data will be simply displayed as a __u64.
 */
#define ID_UNKNOWN 0xffffffff

struct value {
	char name[MAX_STR];
	enum { ARG1, ARG2, ARG3, ARG4, ARG5, RETURN } base_arg;
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

struct btf *btf_load_vmlinux(void);
struct btf *btf_load_module(const char *module, struct btf **base);

const char *btf_kind_name(int kind);

int btf_has_ksym(const char *ksym);
int btf_has_kfunc(const char *kfunc);
int btf_has_struct(const char *sname);
int btf_has_decl_tag(const char *ksym);
