/**
 * Test btf dump
 */
#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "btf_helpers.h"

static void usage(void)
{
	fprintf(stderr,
		"\033[2m\n"
		"Usage: ./btf_dump struct=<ksym|ALL> func=<ksym> mod=<kmod>\n"
		"\n"
		"Examples:\n"
		" ./btf_dump struct=task_struct\n"
		" ./btf_dump mod=kvm struct=task_struct\n"
		" ./btf_dump struct=ALL\n"
		" ./btf_dump mod=kvm struct=ALL\n"
		"\033[m");
}

static void dump_printf(void *ctx, const char *fmt, va_list args)
{
	vprintf(fmt, args);
}

static void dump_btf_id(const struct btf *btf, struct btf_dump *dump,
			int btf_id)
{
	const struct btf_type *t = btf__type_by_id(btf, btf_id);
	const char *name = btf__name_by_offset(btf, t->name_off);
	printf("\033[2m/* btf id %d, name %s, type %s */\033[m\n", btf_id, name,
	       btf_kind_name(BTF_INFO_KIND(t->info)));
	btf_dump__dump_type(dump, btf_id);
}

int main(int argc, char *argv[])
{
	int err = 0;
	struct btf *btf, *base = NULL;
	struct btf_dump *dump;
	char *mod = NULL;
	int btf_id;
	char *sym_struct = "task_struct";
	char *sym_func = NULL;

	for (int i = 1; i < argc; i++) {
		if (!strncmp(argv[i], "struct=", 7)) {
			sym_struct = argv[i] + 7;
		} else if (!strncmp(argv[i], "func=", 5)) {
			if (sym_func) {
				fprintf(stderr,
					"ERROR: must specify func= once, %s\n",
					argv[i]);
				exit(EXIT_FAILURE);
			}
			sym_func = argv[i] + 5;
		} else if (!strncmp(argv[i], "mod=", 4)) {
			if (mod) {
				fprintf(stderr,
					"ERROR: must specify mod= once, %s\n",
					argv[i]);
				exit(EXIT_FAILURE);
			}
			mod = argv[i] + 4;
		} else {
			usage();
			fprintf(stderr, "ERROR: Unknown %s\n", argv[i]);
			exit(EXIT_FAILURE);
		}
	}

	if (mod)
		btf = btf_load_module(mod, &base);
	else
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

	/**
	 * It's seems like function dump nothing with btf_dump__dump_type().
	 */
	if (sym_func) {
		btf_id = btf_has_kfunc(btf, sym_func, false);
		if (btf_id <= 0) {
			fprintf(stderr, "ERROR: not found func %s\n", sym_func);
			err = -ENOENT;
		}
	} else {
		btf_id = btf_has_struct(btf, sym_struct, false);
		if (btf_id <= 0 && strcmp(sym_struct, "ALL"))
			err = -ENOENT;
	}

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
	} else if (!strcmp(sym_struct, "ALL")) {
		int start_id = 1;
		if (base)
			start_id = btf__type_cnt(base);
		for (btf_id = start_id; btf_id < btf__type_cnt(btf); btf_id++) {
			dump_btf_id(btf, dump, btf_id);
		}
	} else {
		dump_btf_id(btf, dump, btf_id);
	}

	printf("btf__type_cnt is %d, %s\n", btf__type_cnt(btf),
	       mod ?: "vmlinux");
	printf("btf_id = %d\n", btf_id);

	btf_dump__free(dump);
	btf__free(btf);
	if (base)
		btf__free(base);
	usage();
	return err;
}
