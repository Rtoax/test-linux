// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/version.h>

#include "btf_helpers.h"


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
	/**
	 * linux commit 8fd886911a6a ("bpf: Add BTF_KIND_FLOAT to uapi")
	 * v5.11-4625-g8fd886911a6a
	 * linux commit 22541a9eeb0d ("libbpf: Add BTF_KIND_FLOAT support")
	 * v5.11-4627-g22541a9eeb0d
	 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 11, 0)
	KIND(BTF_KIND_FLOAT);
#endif
	/**
	 * linux commit 223f903e9c83 ("bpf: Rename BTF_KIND_TAG to BTF_KIND_DECL_TAG")
	 * v5.15-rc3-1032-g223f903e9c83
	 * linux commit b5ea834dde6b ("bpf: Support for new btf kind BTF_KIND_TAG")
	 * v5.14-9734-gb5ea834dde6b
	 */
#if LINUX_VERSION_CODE > KERNEL_VERSION(5, 14, 0) && LINUX_VERSION_CODE < KERNEL_VERSION(5, 15, 0)
	KIND(BTF_KIND_TAG);
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(5, 15, 0)
	KIND(BTF_KIND_DECL_TAG);
#endif
	/**
	 * linux commit 8c42d2fa4eea ("bpf: Support BTF_KIND_TYPE_TAG for btf_type_tag attributes")
	 * v5.15-4637-g8c42d2fa4eea
	 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 15, 0)
	KIND(BTF_KIND_TYPE_TAG);
#endif
	/**
	 * linux commit 6089fb325cf7 ("bpf: Add btf enum64 support")
	 * v5.18-12137-g6089fb325cf7
	 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 18, 0)
	KIND(BTF_KIND_ENUM64);
#endif
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

static int get_func_btf(struct btf *btf, const char *func)
{
	int btf_id = btf__find_by_name_kind(btf, func, BTF_KIND_FUNC);
	return btf_id;
}

static int __btf_has_ksym(const char *ksym, int kind)
{
	struct btf *btf;
	int btf_id;

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
		return -1;
	}

	switch (kind) {
	case BTF_KIND_FUNC:
		btf_id = get_func_btf(btf, ksym);
	case BTF_KIND_DECL_TAG:
		btf_id = btf__find_by_name_kind(btf, ksym, BTF_KIND_DECL_TAG);
	case BTF_KIND_UNKN:
	default:
		btf_id = btf__find_by_name(btf, ksym);
	}
	if (btf_id < 0) {
#ifdef DEBUG
		fprintf(stderr, "ksym '%s' does not exist\n", ksym);
#endif
		btf__free(btf);
		return 0;
	}

#ifdef DEBUG
	const struct btf_type *type;
	type = btf__type_by_id(btf, btf_id);
	printf("ksym '%s' exists with ID %d, KIND %s\n", ksym, btf_id,
		btf_kind_name(btf_kind(type)));
#endif

	btf__free(btf);
	return 1;
}

int btf_has_ksym(const char *ksym)
{
	return __btf_has_ksym(ksym, BTF_KIND_UNKN);
}

int btf_has_kfunc(const char *kfunc)
{
	return __btf_has_ksym(kfunc, BTF_KIND_FUNC);
}

int btf_has_decl_tag(const char *ksym)
{
	return __btf_has_ksym(ksym, BTF_KIND_DECL_TAG);
}
