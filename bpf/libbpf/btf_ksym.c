#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "btf_helpers.h"

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <ksym_name>\n", argv[0]);
		return 1;
	}

	int result;
	const char *ksym_name = argv[1];

#ifdef TEST_BTF_KIND_FUNC
#pragma message "defined TEST_BTF_KIND_FUNC"
	result = btf_check_kfunc_existence(ksym_name);
#elif defined(TEST_BTF_KIND_DECL_TAG)
#pragma message "defined TEST_BTF_KIND_DECL_TAG"
	result = btf_check_decl_tag_existence(ksym_name);
#else
	result = btf_check_ksym_existence(ksym_name);
#endif

	if (result > 0) {
		printf("Kernel symbol '%s' exists.\n", ksym_name);
	} else if (result == 0) {
		printf("Kernel symbol '%s' does not exist.\n", ksym_name);
	}

	return 0;
}
