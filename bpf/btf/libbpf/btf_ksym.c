#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "btf_helpers.h"

static void usage(void)
{
	fprintf(stderr,
		"\033[2m\n"
		"Usage: ./btf_dump struct=<ksym> func=<ksym> decl-tag=<ksym>\n"
		"\033[m");
}

int main(int argc, char **argv)
{
	int err = 0;
	int btf_id;
	const char *ksym = NULL;
	int kind = BTF_KIND_UNKN;

	for (int i = 1; i < argc; i++) {
		if (!strncmp(argv[i], "struct=", 7)) {
			ksym = argv[i] + 7;
			kind = BTF_KIND_STRUCT;
		} else if (!strncmp(argv[i], "func=", 5)) {
			ksym = argv[i] + 5;
			kind = BTF_KIND_FUNC;
		} else if (!strncmp(argv[i], "decl-tag=", 9)) {
			ksym = argv[i] + 9;
			kind = BTF_KIND_DECL_TAG;
		} else {
			ksym = argv[i];
		}
	}
	if (!ksym) {
		usage();
		exit(EXIT_FAILURE);
	}

	switch (kind) {
	case BTF_KIND_STRUCT:
		btf_id = btf_has_struct(ksym);
		break;
	case BTF_KIND_FUNC:
		btf_id = btf_has_kfunc(ksym, true);
		break;
	case BTF_KIND_DECL_TAG:
		btf_id = btf_has_decl_tag(ksym);
		break;
	default:
		btf_id = btf_has_ksym(ksym, &kind);
		break;
	}

	if (btf_id <= 0) {
		printf("Kernel symbol '%s' %s does not exist.\n", ksym,
		       btf_kind_name(kind));
		err = -ENOENT;
	} else
		printf("Kernel symbol '%s' %s exist, btf id %d.\n", ksym,
		       btf_kind_name(kind), btf_id);
	return err;
}
