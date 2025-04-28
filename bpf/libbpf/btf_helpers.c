#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "btf_helpers.h"


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
	KIND(BTF_KIND_DECL_TAG);
	KIND(BTF_KIND_TYPE_TAG);
	KIND(BTF_KIND_ENUM64);
	}
#undef KIND
	abort();
}

static int __btf_has_ksym(const char *ksym, int kind)
{
	struct btf *btf;
	int btf_id;

#if (LIBBPF_MAJOR_VERSION == 0 && LIBBPF_MINOR_VERSION > 5) || (LIBBPF_MAJOR_VERSION >= 1)
	/**
	 * LIBBPF_0.5.0
	 * libbpf commit e65d12890333 ("libbpf: Add btf__load_vmlinux_btf/btf__load_module_btf")
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
		btf_id = btf__find_by_name_kind(btf, ksym, BTF_KIND_FUNC);
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
