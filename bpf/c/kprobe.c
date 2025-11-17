#include <stdio.h>
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

enum insn_type {
	INSN_TRACE_PRINTK,
	INSN_CGROUP_FROM_ID,
};

char bpf_log_buf[BPF_LOG_BUF_SIZE];

int main(int argc, char *argv[])
{
	int i, prog_fd;
	int prog_type = BPF_PROG_TYPE_KPROBE;
	enum insn_type insn_type = INSN_TRACE_PRINTK;
	char *insn_name = "";
	size_t insns_cnt;
	char license[] = "GPL";
	struct bpf_insn *insns;

	printf("%s [trace_printk|cgroup_from_id] [tracepoint]\n", argv[0]);
	for (i = 1; i < argc; i++) {
		if (!strcmp("cgroup_from_id", argv[i]))
			insn_type = INSN_CGROUP_FROM_ID;
		if (!strcmp("tracepoint", argv[i]))
			prog_type = BPF_PROG_TYPE_TRACEPOINT;
	}

	switch (insn_type) {
	case INSN_CGROUP_FROM_ID:
		insns = cgroup_from_id_insns(&insns_cnt);
		insn_name = "cgroup_from_id";
		break;
	case INSN_TRACE_PRINTK:
	default:
		insns = trace_printk_insns(&insns_cnt);
		insn_name = "trace_printk";
		break;
	}

	printf("Prog %s has %ld insns\n", insn_name, insns_cnt);

	union bpf_attr prog_load_attr = {
		.prog_type = prog_type,
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

#if defined(HAVE_BCC)
	int probe_fd;
	if (prog_type == BPF_PROG_TYPE_TRACEPOINT) {
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
	close(probe_fd);
	if (prog_type == BPF_PROG_TYPE_TRACEPOINT) {
		bpf_detach_tracepoint("syscalls", "sys_enter_nanosleep");
	} else {
		bpf_detach_kprobe("hello_world");
	}
#else
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
#endif
	close(prog_fd);
	return 0;
}
