#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <stdint.h>
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
	char *sym_struct = "task_struct";

	if (argc > 1)
		sym_struct = argv[1];

	btf = btf_load_vmlinux();
	if (!btf) {
		fprintf(stderr, "btf load failed.\n");
		exit(EXIT_FAILURE);
	}
	dump = btf_dump__new(btf, dump_printf, NULL, NULL);
	if (!dump) {
		fprintf(stderr, "btf dump create failed.\n");
		exit(EXIT_FAILURE);
	}

	btf_id = btf_has_struct(sym_struct);

	/**
	 * If input none arguments
	 */
	if (argc == 1 && !strcmp(sym_struct, "task_struct")) {
		struct task_struct {
			struct thread_info {
				long unsigned int flags;
				long unsigned int syscall_work;
				uint32_t status;
				uint32_t cpu;
			} thread_info;
		};
		struct task_struct task = {
			.thread_info = {
				.flags = 2,
				.syscall_work = 3,
				.status = 4,
				.cpu = 5,
			},
		};

		DECLARE_LIBBPF_OPTS(btf_dump_type_data_opts, opts,
				    .compact = false, .skip_names = false, );
		btf_dump__dump_type_data(dump, btf_id, &task, sizeof(task),
					 &opts);
	} else {
		btf_dump__dump_type(dump, btf_id);
	}

	btf_dump__free(dump);
	btf__free(btf);
	return 0;
}
