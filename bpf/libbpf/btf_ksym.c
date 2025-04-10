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
	int func_id;

	btf = btf__parse(sysfs_vmlinux, NULL);
	if (!btf) {
		fprintf(stderr, "Failed to parse BTF\n");
		return -1;
	}

	func_id = btf__find_by_name(btf, ksym_name);
	if (func_id < 0) {
#ifdef DEBUG
		fprintf(stderr, "ksym '%s' does not exist\n", ksym_name);
#endif
		btf__free(btf);
		return 0;
	}

#ifdef DEBUG
	printf("ksym '%s' exists with ID %d\n", ksym_name, func_id);
#endif

	btf__free(btf);
	return 1;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <ksym_name>\n", argv[0]);
		return 1;
	}

	const char *ksym_name = argv[1];
	int result = check_ksym_existence(ksym_name);

	if (result > 0) {
		printf("Kernel symbol '%s' exists.\n", ksym_name);
	} else if (result == 0) {
		printf("Kernel symbol '%s' does not exist.\n", ksym_name);
	}

	return 0;
}
