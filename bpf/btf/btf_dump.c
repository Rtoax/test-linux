#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "btf_helpers.h"

static void dump_printf(void *ctx, const char *fmt, va_list args)
{
	vprintf(fmt, args);
}

int main(int argc, char **argv)
{
	struct btf *btf;
	struct btf_dump *dump;
	int btf_id;

	btf = btf_load_vmlinux();
	dump = btf_dump__new(btf, dump_printf, NULL, NULL);
	if (!dump) {
		fprintf(stderr, "btf dump new failed.\n");
	}

	btf_id = btf_has_struct("task_struct");

	btf_dump__dump_type(dump, btf_id);

	btf_dump__free(dump);
	btf__free(btf);
	return 0;
}
