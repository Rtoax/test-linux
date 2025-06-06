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

	BPF__OPEN_AND_LOAD(skel, _bpf__open_and_load, _bpf__open_opts,
			_bpf__load, _bpf__destroy);

	err = _bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	printf("Successfully started!\n");

	read_trace_pipe();

cleanup:
	printf("Goodbye!!\n");
	_bpf__destroy(skel);
	return -err;
}
