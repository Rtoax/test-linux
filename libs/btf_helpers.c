// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/version.h>
#include "btf_helpers.h"

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

enum {
	/**
	 * linux commit 8fd886911a6a ("bpf: Add BTF_KIND_FLOAT to uapi")
	 * v5.11-4625-g8fd886911a6a
	 * linux commit 22541a9eeb0d ("libbpf: Add BTF_KIND_FLOAT support")
	 * v5.11-4627-g22541a9eeb0d
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 11, 0) && !defined(BTF_KIND_FLOAT)
	BTF_KIND_FLOAT = 16,
#endif
	/**
	 * linux commit 223f903e9c83 ("bpf: Rename BTF_KIND_TAG to BTF_KIND_DECL_TAG")
	 * v5.15-rc3-1032-g223f903e9c83
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 15, 0) && !defined(BTF_KIND_DECL_TAG)
	BTF_KIND_DECL_TAG = 17,
#endif
	/**
	 * linux commit 8c42d2fa4eea ("bpf: Support BTF_KIND_TYPE_TAG for btf_type_tag attributes")
	 * v5.15-4637-g8c42d2fa4eea
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 15, 0) && !defined(BTF_KIND_TYPE_TAG)
	BTF_KIND_TYPE_TAG = 18,
#endif
	/**
	 * linux commit 6089fb325cf7 ("bpf: Add btf enum64 support")
	 * v5.18-12137-g6089fb325cf7
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 18, 0) && !defined(BTF_KIND_ENUM64)
	BTF_KIND_ENUM64 = 19,
#endif
	_____EMPTY_IS_NOT_ALLOW,
};

/**
 * linux commit 41ced4cd8802 ("btf: Change BTF_KIND_* macros to enums")
 * v5.14-9733-g41ced4cd8802
 */
const char *btf_kind_name(int kind)
{
#define KIND(v) case v: return #v;
	switch (kind) {
	KIND(BTF_KIND_UNKN);
	KIND(BTF_KIND_INT);
	KIND(BTF_KIND_PTR);
	KIND(BTF_KIND_ARRAY);
	KIND(BTF_KIND_STRUCT);
	KIND(BTF_KIND_UNION);
	KIND(BTF_KIND_ENUM);
	KIND(BTF_KIND_FWD);
	KIND(BTF_KIND_TYPEDEF);
	KIND(BTF_KIND_VOLATILE);
	KIND(BTF_KIND_CONST);
	KIND(BTF_KIND_RESTRICT);
	KIND(BTF_KIND_FUNC);
	KIND(BTF_KIND_FUNC_PROTO);
	KIND(BTF_KIND_VAR);
	KIND(BTF_KIND_DATASEC);
	KIND(BTF_KIND_FLOAT);
	/**
	 * linux commit b5ea834dde6b ("bpf: Support for new btf kind BTF_KIND_TAG")
	 * v5.14-9734-gb5ea834dde6b
	 */
#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 14, 0) && LINUX_VERSION_CODE < KERNEL_VERSION(5, 15, 0)
	KIND(BTF_KIND_TAG);
#endif
	KIND(BTF_KIND_DECL_TAG);
	KIND(BTF_KIND_TYPE_TAG);
	KIND(BTF_KIND_ENUM64);
	}
#undef KIND
	fprintf(stderr, "ERROR: Invalid or kernel not support kind %d\n", kind);
	if (kind > 0 && kind < NR_BTF_KINDS) {
		static const char *names[] = {
			"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
			"11", "12", "13", "14", "15", "16", "17", "18", "19",
			"20", "21"};
		return names[kind];
	}
	abort();
}

void print_btf(const struct btf *btf)
{
	// TODO:
}

static void type_to_value(const struct btf *btf, char *name, __u32 type_id,
			  struct value *val)
{
	const struct btf_type *type;
	__s32 id = type_id;

	if (name)
		strncpy(val->name, name, sizeof(val->name) - 1);
	else
		val->name[0] = '\0';

	do {
		type = btf__type_by_id(btf, id);
		switch (BTF_INFO_KIND(type->info)) {
		case BTF_KIND_CONST:
		case BTF_KIND_VOLATILE:
		case BTF_KIND_RESTRICT:
		case BTF_KIND_PTR:
			val->flags |= F_PTR;
			id = type->type;
			break;
		default:
			/* FIXME: set id */
			val->type_id = id;
			goto done;
		}
	} while (id >= 0);

	val->type_id = ID_UNKNOWN;

done:
	val->size = btf__resolve_size(btf, val->type_id);
}

static char *type_id_to_str(const struct btf *btf, __s32 type_id, char *buf)
{
	const struct btf_type *type;
	const char *name = "";
	char *prefix = "";
	char *suffix = " ";
	char *ptr = "";
	bool anonymous = false;

	buf[0] = '\0';

	switch (type_id) {
	case 0:
		name = "void";
		break;
	case ID_UNKNOWN:
		name = "?";
		break;
	default:
		do {
			type = btf__type_by_id(btf, type_id);
			if (!type) {
				name = "?";
				break;
			}
			if (type->name_off == 0)
				anonymous = true;

			switch (BTF_INFO_KIND(type->info)) {
			case BTF_KIND_CONST:
			case BTF_KIND_VOLATILE:
			case BTF_KIND_RESTRICT:
				type_id = type->type;
				break;
			case BTF_KIND_PTR:
				ptr = "* ";
				type_id = type->type;
				break;
			case BTF_KIND_ARRAY: {
				//const struct btf_array *arr = btf_array(type);
				suffix = "[]";
				type_id = type->type;
				break;
			}
			case BTF_KIND_STRUCT:
				prefix = "struct ";
				name = btf__str_by_offset(btf, type->name_off);
				break;
			case BTF_KIND_UNION:
				prefix = "union ";
				name = btf__str_by_offset(btf, type->name_off);
				break;
			case BTF_KIND_ENUM:
				prefix = "enum ";
				name = btf__str_by_offset(btf, type->name_off);
				break;
			case BTF_KIND_TYPEDEF:
			default:
				name = btf__str_by_offset(btf, type->name_off);
				break;
			}
		} while (type_id >= 0 && (strlen(name) == 0 && !anonymous));
		break;
	}
	snprintf(buf, MAX_STR, "%s%s%s%s", prefix, name, suffix, ptr);
	return buf;
}

static char *value_to_str(const struct btf *btf, struct value *val, char *str)
{
	str = type_id_to_str(btf, val->type_id, str);
	if (val->flags & F_PTR)
		strncat(str, "*", MAX_STR);
	if (strlen(val->name) > 0 && strcmp(val->name, "return") != 0)
		strncat(str, val->name, MAX_STR);
	return str;
}

static int get_func_btf_id(const struct btf *btf, const char *name, bool dump)
{
	int i, btf_id;
	const struct btf_type *type;
	const struct btf_param *param;
	struct func func;
	char str[MAX_STR];

	snprintf(func.name, MAX_NAME, "%s", name);

	btf_id = btf__find_by_name_kind(btf, name, BTF_KIND_FUNC);
	if (btf_id <= 0)
		return -ENOENT;

	if (!dump)
		return btf_id;

	type = btf__type_by_id(btf, btf_id);
	if (!type || BTF_INFO_KIND(type->info) != BTF_KIND_FUNC)
		return -ENOENT;
	type = btf__type_by_id(btf, type->type);
	if (!type || BTF_INFO_KIND(type->info) != BTF_KIND_FUNC_PROTO)
		return -EINVAL;

	for (param = (struct btf_param *)(type + 1), i = 0;
	     i < BTF_INFO_VLEN(type->info) && i < MAX_ARGS;
	     param++, i++) {
		type_to_value(btf,
			      (char *)btf__str_by_offset(btf, param->name_off),
			      param->type, &func.args[i]);
	}

	func.nr_args = BTF_INFO_VLEN(type->info);

	type_to_value(btf, "return", type->type, &func.args[RETURN]);

	/* print function */
	printf("%s%s(", value_to_str(btf, &func.args[RETURN], str), func.name);
	for (i = 0; i < func.nr_args; i++) {
		if (i > 0)
			printf(", ");
		printf("%s", value_to_str(btf, &func.args[i], str));
	}
	if (func.nr_args > MAX_ARGS)
		printf("/* and %d more args that are not traceable */",
			func.nr_args - MAX_ARGS);
	printf(") = btf_id %d;\n", btf_id);
	return btf_id;
}

static int get_struct_btf(const struct btf *btf, const char *name, bool dump)
{
	int i, btf_id, vlen;
	const struct btf_type *type;
	const struct btf_member *member;

	btf_id = btf__find_by_name_kind(btf, name, BTF_KIND_STRUCT);
	if (btf_id <= 0)
		return -ENOENT;

	type = btf__type_by_id(btf, btf_id);
	if (!type || BTF_INFO_KIND(type->info) != BTF_KIND_STRUCT)
		return -ENOENT;

	if (!dump)
		return btf_id;

	vlen = BTF_INFO_VLEN(type->info);
	member = (const struct btf_member *)(type + 1);

	printf("struct %s {\n", name);
	for (i = 0; i < vlen; i++) {
		struct value val;
		char str[MAX_STR];
		const char *member_name = btf__name_by_offset(btf, member[i].name_off);

		memset(&val, 0 , sizeof(val));
		memset(&str, 0 , sizeof(str));

		type_to_value(btf, NULL, member[i].type, &val);

		printf("    %s %s;\n", value_to_str(btf, &val, str), member_name);
	}
	printf("};\n");

	return btf_id;
}

struct btf *btf_load_vmlinux(void)
{
	struct btf *btf;

#if (LIBBPF_MAJOR_VERSION == 0 && LIBBPF_MINOR_VERSION > 5) || (LIBBPF_MAJOR_VERSION >= 1)
	/**
	 * LIBBPF_0.5.0
	 * libbpf commit e65d12890333 ("libbpf: Add btf__load_vmlinux_btf/btf__load_module_btf")
	 *
	 * struct btf *libbpf_find_kernel_btf(void) __attribute__((alias("btf__load_vmlinux_btf")));
	 */
	btf = btf__load_vmlinux_btf();
#else
	/**
	 * LIBBPF_0.0.4
	 */
	btf = btf__parse(SYSFS_VMLINUX, NULL);
#endif

	if (!btf) {
		fprintf(stderr, "Failed to parse BTF\n");
		return NULL;
	}
	return btf;
}

/**
 * If module is not base BTF, parse the base BTF first, point to base.
 */
struct btf *btf_load_module(const char *module, struct btf **base)
{
	if (!strcmp(module, "vmlinux"))
		return btf_load_vmlinux();

	char path[64];
	snprintf(path, 64, "/sys/kernel/btf/%s", module);
	/**
	 * To save storage space and avoid duplication, the Linux kernel's BTF
	 * information is divided into two parts:
	 *
	 * Base BTF (vmlinux): Contains all type definitions for the kernel
	 * core; it's the system's "type dictionary."
	 *
	 * Split BTF (kvm, i915, etc. modules): Each kernel module's BTF file is
	 * an "incremental package," containing only the new type definitions
	 * specific to that module. For a type that already exists in vmlinux
	 * (such as `struct task_struct`), it is not redefined in the module's
	 * BTF; instead, it is referred to by its ID in vmlinux.
	 */
	*base = btf_load_vmlinux();
	return btf__parse_split(path, *base);
}

/**
 * Return btf id if exist, -1 if non-exist.
 */
static int __btf_has_ksym(const struct btf *btf, const char *ksym, int kind,
			  int *realkind, bool dump)
{
	int btf_id;
	int need_free_btf = 0;

	if (!btf) {
		need_free_btf = 1;
		btf = btf_load_vmlinux();
	}

	switch (kind) {
	case BTF_KIND_FUNC:
		btf_id = get_func_btf_id(btf, ksym, dump);
		break;
	case BTF_KIND_DECL_TAG:
		btf_id = btf__find_by_name_kind(btf, ksym, BTF_KIND_DECL_TAG);
		break;
	case BTF_KIND_STRUCT:
		btf_id = get_struct_btf(btf, ksym, dump);
		break;
	case BTF_KIND_UNKN:
	default:
		btf_id = btf__find_by_name(btf, ksym);
		if (realkind) {
			const struct btf_type *type =
				btf__type_by_id(btf, btf_id);
			if (type)
				*realkind = BTF_INFO_KIND(type->info);
		}
		break;
	}

	if (btf_id < 0) {
#ifdef DEBUG
		fprintf(stderr, "ksym '%s' does not exist\n", ksym);
#endif
		if (need_free_btf)
			btf__free((void *)btf);
		return -ENOENT;
	}

#ifdef DEBUG
	const struct btf_type *type;
	type = btf__type_by_id(btf, btf_id);
	printf("ksym '%s' exists with ID %d, KIND %s\n", ksym, btf_id,
		btf_kind_name(btf_kind(type)));
#endif

	if (need_free_btf)
		btf__free((void *)btf);
	return btf_id;
}

int btf_has_ksym(const struct btf *btf, const char *ksym, int *kind)
{
	return __btf_has_ksym(btf, ksym, BTF_KIND_UNKN, kind, true);
}

int btf_has_kfunc(const struct btf *btf, const char *kfunc, bool dump)
{
	return __btf_has_ksym(btf, kfunc, BTF_KIND_FUNC, NULL, dump);
}

int btf_has_struct(const struct btf *btf, const char *sname, bool dump)
{
	return __btf_has_ksym(btf, sname, BTF_KIND_STRUCT, NULL, dump);
}

int btf_has_union(const struct btf *btf, const char *sname)
{
	return __btf_has_ksym(btf, sname, BTF_KIND_UNION, NULL, true);
}

int btf_has_enum(const struct btf *btf, const char *sname)
{
	return __btf_has_ksym(btf, sname, BTF_KIND_ENUM, NULL, true);
}

int btf_has_enum64(const struct btf *btf, const char *sname)
{
	return __btf_has_ksym(btf, sname, BTF_KIND_ENUM64, NULL, true);
}

int btf_has_decl_tag(const struct btf *btf, const char *ksym)
{
	return __btf_has_ksym(btf, ksym, BTF_KIND_DECL_TAG, NULL, true);
}
