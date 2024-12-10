#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <bpf/libbpf.h>
#include "socket_filter.skel.h"


static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	if (level >= LIBBPF_DEBUG)
		return 0;

	return vfprintf(stderr, format, args);
}

int main(void)
{
	int i, err;
	struct socket_filter_bpf *skel;

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	skel = socket_filter_bpf__open();
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	fprintf(stderr, "Prog count %d\n", skel->skeleton->prog_cnt);
	bpf_program__set_type(skel->progs.bpf_prog1, BPF_PROG_TYPE_SOCKET_FILTER);

	err = socket_filter_bpf__load(skel);
	if (err) {
		socket_filter_bpf__destroy(skel);
		return 1;
	}

	socket_filter_bpf__destroy(skel);
	return 0;
}
