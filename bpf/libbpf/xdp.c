#include <argp.h>
#include <arpa/inet.h>
#include <assert.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/if_packet.h>
#include <linux/in.h>
#include <net/if.h>
#include <signal.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <unistd.h>
#include "xdp.skel.h"

static volatile bool exiting = false;

int ifindex = -1;
const char *interface;

const char argp_prog_doc[] =
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
	exiting = true;
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
	struct xdp_bpf *skel;
	int xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

	libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (ifindex == -1) {
		fprintf(stderr, "Need specify interface with -i\n");
		return -EINVAL;
	}

	skel = xdp_bpf__open();
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	fprintf(stderr, "Track interface %s, index %d\n", interface, ifindex);
	fprintf(stderr, "Prog count %d\n", skel->skeleton->prog_cnt);
#if !defined(STRICT_SEC_NAME)
	bpf_program__set_type(skel->progs.xdp_pass, BPF_PROG_TYPE_XDP);
#endif

	err = xdp_bpf__load(skel);
	if (err) {
		xdp_bpf__destroy(skel);
		return 1;
	}

	/* Attach BPF program to raw socket */
	prog_fd = bpf_program__fd(skel->progs.xdp_pass);

/**
 * libbpf commit e8802d6319ab ("libbpf: remove deprecated XDP APIs") remove
 * bpf_set_link_xdp_fd(), libbpf version v1.0.0
 */
#if LIBBPF_MAJOR_VERSION >= 1
	err = bpf_xdp_attach(ifindex, prog_fd, xdp_flags, NULL);
#else
	err = bpf_set_link_xdp_fd(ifindex, prog_fd, xdp_flags);
#endif
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

	/* Process events */
	while (!exiting) {
		sleep(1);
	}

cleanup:
	printf("Detach xdp from interface %s\n", interface);
	/**
	 * Like: sudo bpftool net detach xdp dev $interface
	 */
/**
 * libbpf commit e8802d6319ab ("libbpf: remove deprecated XDP APIs") remove
 * bpf_set_link_xdp_fd(), libbpf version v1.0.0
 */
#if LIBBPF_MAJOR_VERSION >= 1
	bpf_xdp_detach(ifindex, xdp_flags, NULL);
#else
	bpf_set_link_xdp_fd(ifindex, -1, xdp_flags);
#endif
	xdp_bpf__destroy(skel);
	return 0;
}
