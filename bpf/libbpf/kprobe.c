// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "trace_helpers.h"
#include "libbpf_wrapper.h"
#define __USER__
#include "stack_helpers.h"

#if defined(KPROBE)
#include "kprobe.skel.h"
#define NAME kprobe
#include "skel_defs.h"
#elif defined(FENTRY)
#include "fentry.skel.h"
#define NAME fentry
#include "skel_defs.h"
#elif defined(FMOD_RET)
#include "fmod_ret.skel.h"
#define NAME fmod_ret
#include "skel_defs.h"
#else
#error "Not support skel"
#endif

void sig_handler(int sig)
{
	read_trace_pipe_stop();
}

int main(int argc, char **argv)
{
	struct struct_bpf *skel;
	int err;

	signal(SIGINT, sig_handler);

	libbpf_set_print(libbpf_print_fn);

	skel = BPF__OPEN_AND_LOAD(_bpf__open_and_load, _bpf__open_opts,
			_bpf__load, _bpf__destroy);

	struct ksyms *ksyms = load_kallsyms();

	init_stackmap(skel->maps.stackmap, 1024);

	err = _bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	printf("Successfully started!\n");

	read_trace_pipe();

cleanup:
	printf("Goodbye!!\n");
	print_stack(bpf_map__fd(skel->maps.stackmap), ksyms);
	_bpf__destroy(skel);
	free_kallsyms(ksyms);
	return -err;
}
