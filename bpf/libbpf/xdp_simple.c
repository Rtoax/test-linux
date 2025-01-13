#include <argp.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/if_packet.h>
#include <linux/if_xdp.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <malloc.h>
#include <net/if.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <unistd.h>

#include "trace_helpers.h"
#include "libbpf_wrapper.h"

#include "xdp_simple.skel.h"

#define struct_bpf	xdp_simple_bpf
#define _bpf__open	xdp_simple_bpf__open
#define _bpf__load	xdp_simple_bpf__load
#define _bpf__destroy	xdp_simple_bpf__destroy

static int ifindex = -1;
static const char *interface;

static const char argp_prog_doc[] =
	"USAGE: [-i <interface>]\n";

static const struct argp_option opts[] = {
	{ "interface", 'i', "INTERFACE", 0, "Network interface to attach" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'i':
		interface = arg;
		ifindex = if_nametoindex(interface);
		if (!ifindex)
			ifindex = atoi(interface);
		break;
	case ARGP_KEY_ARG:
		argp_usage(state);
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

static void sig_handler(int sig)
{
	stop_read_trace_pipe();
}

static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	if (level >= LIBBPF_DEBUG)
		return 0;

	return vfprintf(stderr, format, args);
}

int main(int argc, char *argv[])
{
	int err, prog_fd;
	struct struct_bpf *skel;
	int xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGABRT, sig_handler);

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (ifindex == -1) {
		fprintf(stderr, "Need specify interface with -i\n");
		return -EINVAL;
	}

	skel = _bpf__open();
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	fprintf(stderr, "Prog count %d\n", skel->skeleton->prog_cnt);

	bpf_program__set_type(skel->progs.xdp_dummy_prog, BPF_PROG_TYPE_XDP);

	err = _bpf__load(skel);
	if (err) {
		_bpf__destroy(skel);
		return 1;
	}

	prog_fd = bpf_program__fd(skel->progs.xdp_dummy_prog);

	err = tl_bpf_xdp_attach(ifindex, prog_fd, xdp_flags);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

	/* Process events */
	read_trace_pipe();

cleanup:
	printf("Detach xdp from interface %s\n", interface);
	tl_bpf_xdp_detach(ifindex, xdp_flags);
	_bpf__destroy(skel);
	return 0;
}
