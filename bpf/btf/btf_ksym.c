#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "btf_helpers.h"

int main(int argc, char **argv)
{
	int btf_id;
	char *s_type = "";
	const char *ksym;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <ksym>\n", argv[0]);
		return 1;
	}

	ksym = argv[1];

#ifdef TEST_BTF_KIND_FUNC
#pragma message "defined TEST_BTF_KIND_FUNC"
	btf_id = btf_has_kfunc(ksym);
	s_type = "FUNC";
#elif defined(TEST_BTF_KIND_STRUCT)
#pragma message "defined TEST_BTF_KIND_STRUCT"
	btf_id = btf_has_struct(ksym);
	s_type = "STRUCT";
#elif defined(TEST_BTF_KIND_DECL_TAG)
#pragma message "defined TEST_BTF_KIND_DECL_TAG"
	btf_id = btf_has_decl_tag(ksym);
	s_type = "DECL_TAG";
#else
	btf_id = btf_has_ksym(ksym);
	if (btf_id > 0)
		printf("Kernel symbol '%s' exist.\n", ksym);
#endif

	if (btf_id <= 0)
		printf("Kernel symbol '%s' %s does not exist.\n", ksym, s_type);
	else
		printf("Kernel symbol '%s' %s exist, btf id %d.\n", ksym,
			s_type, btf_id);
	return 0;
}
