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
	char *s_type = "";
	const char *ksym_name = argv[1];

#ifdef TEST_BTF_KIND_FUNC
#pragma message "defined TEST_BTF_KIND_FUNC"
	result = btf_has_kfunc(ksym_name);
	s_type = "FUNC";
#elif defined(TEST_BTF_KIND_STRUCT)
#pragma message "defined TEST_BTF_KIND_STRUCT"
	result = btf_has_struct(ksym_name);
	s_type = "STRUCT";
#elif defined(TEST_BTF_KIND_DECL_TAG)
#pragma message "defined TEST_BTF_KIND_DECL_TAG"
	result = btf_has_decl_tag(ksym_name);
	s_type = "DECL_TAG";
#else
	result = btf_has_ksym(ksym_name);
	if (result > 0)
		printf("Kernel symbol '%s' exist.\n", ksym_name);
#endif
	if (result <= 0)
		printf("Kernel symbol '%s' %s does not exist.\n", ksym_name, s_type);
	return 0;
}
