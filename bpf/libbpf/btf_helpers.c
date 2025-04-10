#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "btf_helpers.h"


static int __btf_check_ksym_existence(const char *ksym_name, int kind)
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
		btf_id = btf__find_by_name_kind(btf, ksym_name, BTF_KIND_FUNC);
	case BTF_KIND_UNKN:
	default:
		btf_id = btf__find_by_name(btf, ksym_name);
	}
	if (btf_id < 0) {
#ifdef DEBUG
		fprintf(stderr, "ksym '%s' does not exist\n", ksym_name);
#endif
		btf__free(btf);
		return 0;
	}

#ifdef DEBUG
	const struct btf_type *type;
	type = btf__type_by_id(btf, btf_id);
	printf("ksym '%s' exists with ID %d, KIND %d\n", ksym_name, btf_id, btf_kind(type));
#endif

	btf__free(btf);
	return 1;
}

int btf_check_ksym_existence(const char *ksym_name)
{
	return __btf_check_ksym_existence(ksym_name, BTF_KIND_UNKN);
}

int btf_check_kfunc_existence(const char *kfunc_name)
{
	return __btf_check_ksym_existence(kfunc_name, BTF_KIND_FUNC);
}
