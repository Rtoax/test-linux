// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "kprobe.skel.h"
#include "trace_helpers.h"

static volatile sig_atomic_t stop = 0;
static sigjmp_buf jmp;

void sig_handler(int sig)
{
	fprintf(stderr, "get sig...\n");
	stop = 1;
	siglongjmp(jmp, 1);
}

static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	return vfprintf(stderr, format, args);
}

int main(int argc, char **argv)
{
	struct kprobe_bpf *skel;
	int err;

	signal(SIGINT, sig_handler);
	sigsetjmp(jmp, 1);
	if (stop)
		goto cleanup;

	libbpf_set_print(libbpf_print_fn);

	skel = kprobe_bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open BPF skeleton\n");
		return 1;
	}

	err = kprobe_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	printf("Successfully started!\n");

	read_trace_pipe();

cleanup:
	printf("Goodbye!!\n");
	kprobe_bpf__destroy(skel);
	return -err;
}
