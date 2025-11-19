#include <argp.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <bpf/bpf.h>
#include <bcc/libbpf.h>
#include <linux/bpf.h>
#include <linux/version.h>
#include "bpf_helpers.h"
#include "bpf_insn_samples.h"


#define DEBUGFS	"/sys/kernel/debug/tracing"

#ifndef offsetofend
#define offsetofend(TYPE, MEMBER) \
	(offsetof(TYPE, MEMBER)	+ sizeof((((TYPE *)0)->MEMBER)))
#endif

enum load_engine {
	ENGINE_BCC,
	ENGINE_LIBBPF,
	ENGINE_BPF_SYSCALL,
};

struct env {
	enum bpf_prog_type prog_type;
	char *insn_name;
	bpf_samples_get_insns_fn insns_fn;
	enum load_engine engine;
	int verbose;
} env = {
	.prog_type = BPF_PROG_TYPE_KPROBE,
	.insns_fn = bpf_insn_sample_trace_printk_insns,
	.insn_name = "trace_printk",
	.engine = ENGINE_BCC,
	.verbose = false,
};

char bpf_log_buf[BPF_LOG_BUF_SIZE];

const char argp_prog_doc[] =
	"USAGE: [-t <prog-type>] [-h <helper>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "progtype", 't', "PROG_TYPE", 0, "bpf prog type" },
	{ "helper", 'h', "HELPER", 0, "Specify bpf helper or kfunc name" },
	{ "engine", 'e', "ENGINE", 0, "Specify load engine: bcc, libbpf, syscall" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{},
};

enum bpf_prog_type bpf_prog_type_from_string(const char *str)
{
	/* TODO */
	return BPF_PROG_TYPE_TRACEPOINT;
}

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 't':
		env.prog_type = bpf_prog_type_from_string(arg);
		break;
	case 'h':
		env.insns_fn = bpf_samples_get_insns_from_string(arg);
		if (!env.insns_fn) {
			bpf_samples_insns_list();
			printf("\n");
			fprintf(stderr, "ERROR: not found %s\n", arg);
			exit(1);
		}
		env.insn_name = arg;
		break;
	case 'e':
		if (!strcmp(arg, "bcc"))
			env.engine = ENGINE_BCC;
		else if (!strcmp(arg, "libbpf"))
			env.engine = ENGINE_LIBBPF;
		else if (!strcmp(arg, "syscall"))
			env.engine = ENGINE_BPF_SYSCALL;
		else {
			fprintf(stderr, "ERROR: Unknown engine %s\n", arg);
			exit(1);
		}
		break;
	case 'v':
		env.verbose = true;
		break;
	case ARGP_KEY_ARG:
		break;
	case ARGP_KEY_END:
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

int main(int argc, char *argv[])
{
	int i, err, prog_fd;
	size_t insns_cnt;
	char license[] = "GPL";
	struct bpf_insn *insns;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	printf("%s -h [", argv[0]);
	bpf_samples_insns_list();
	printf("] -t [tracepoint|kprobe]\n");

	insns = env.insns_fn(&insns_cnt);

	printf("Prog %s has %ld insns\n", env.insn_name, insns_cnt);

	union bpf_attr prog_load_attr = {
		.prog_type = env.prog_type,
		.insns = (long)insns,
		.insn_cnt = insns_cnt,
		.license = (long)license,
		.log_buf = (long)bpf_log_buf,
		.log_size = sizeof(bpf_log_buf),
		.log_level = 1,
	};

	prog_fd = bpf(BPF_PROG_LOAD, &prog_load_attr, sizeof(prog_load_attr));
	if (prog_fd < 0) {
		printf("ERROR: failed to load prog '%s'\n", strerror(errno));
		return 1;
	}

	unsigned char *p = (void *)&insns;
	for (i = 0; i < insns_cnt * sizeof(struct bpf_insn); i++) {
		unsigned char c = *(p + i);
		printf("%02x ", c);
		if ((i + 1) % 8 == 0)
			printf("\n");
	}

	for (i = 0; i < sizeof(bpf_log_buf); i++) {
		if (bpf_log_buf[i] == 0 && bpf_log_buf[i + 1] == 0)
			break;
		printf("%c", bpf_log_buf[i]);
	}

	int probe_fd;

	if (env.engine == ENGINE_BCC) {
		if (env.prog_type == BPF_PROG_TYPE_TRACEPOINT) {
			probe_fd = bpf_attach_tracepoint(prog_fd, "syscalls", "sys_enter_nanosleep");
			fprintf(stdout, "Tracepoint sys_enter_nanosleep(), test with 'sleep 0.1'.\n");
		} else {
			probe_fd = bpf_attach_kprobe(prog_fd, BPF_PROBE_ENTRY, "hello_world", "do_nanosleep", 0, 0);
			fprintf(stdout, "Kprobe do_nanosleep(), test with 'sleep 0.1'.\n");
		}
		if (prog_fd < 0) {
			printf("ERROR: failed to attach kprobe to do_nanosleep.\n");
			return 2;
		}

		system("cat " DEBUGFS "/trace_pipe");
		if (env.prog_type == BPF_PROG_TYPE_TRACEPOINT) {
			bpf_detach_tracepoint("syscalls", "sys_enter_nanosleep");
		} else {
			bpf_detach_kprobe("hello_world");
		}
	} else if (env.engine == ENGINE_LIBBPF) {
		// TODO
	} else if (env.engine == ENGINE_BPF_SYSCALL) {
		// TODO
		union bpf_attr prog_run_attr;
		size_t attr_sz = offsetofend(union bpf_attr, test);

		memset(&prog_run_attr, 0x0, sizeof(prog_run_attr));
		prog_run_attr.test.prog_fd = prog_fd;
		prog_run_attr.test.ctx_in = 0;

		int err = bpf(BPF_PROG_TEST_RUN, &prog_run_attr, attr_sz);
		if (err < 0 || (int)prog_run_attr.test.retval < 0) {
			if (err < 0)
				fprintf(stderr, "failed to execute loader prog, err = %d\n", err);
			else
				fprintf(stderr, "error returned by loader prog, retval = %d\n",
					prog_run_attr.test.retval);
		}
	}

	close(probe_fd);
	close(prog_fd);
	return 0;
}
