#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const char sysfs_vmlinux[] = "/sys/kernel/btf/vmlinux";

int check_ksym_existence(const char *ksym_name)
{
	struct btf *btf;
	int btf_id;

	btf = btf__parse(sysfs_vmlinux, NULL);
	if (!btf) {
		fprintf(stderr, "Failed to parse BTF\n");
		return -1;
	}

	btf_id = btf__find_by_name(btf, ksym_name);
	if (btf_id < 0) {
#ifdef DEBUG
		fprintf(stderr, "ksym '%s' does not exist\n", ksym_name);
#endif
		btf__free(btf);
		return 0;
	}

#ifdef DEBUG
	printf("ksym '%s' exists with ID %d\n", ksym_name, btf_id);
#endif

	btf__free(btf);
	return 1;
}
