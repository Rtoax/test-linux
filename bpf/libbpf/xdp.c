#include <argp.h>
#include <arpa/inet.h>
#include <assert.h>
#include <setjmp.h>
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

#include "trace_helpers.h"
#include "libbpf_wrapper.h"

#if defined(XDP_BASIC)
#include "xdp.skel.h"
#define struct_bpf	xdp_bpf
#define _bpf__open	xdp_bpf__open
#define _bpf__load	xdp_bpf__load
#define _bpf__destroy	xdp_bpf__destroy
#elif defined(XDP_DEVMAP)
#include "xdp_devmap.skel.h"
#define struct_bpf	xdp_devmap_bpf
#define _bpf__open	xdp_devmap_bpf__open
#define _bpf__load	xdp_devmap_bpf__load
#define _bpf__destroy	xdp_devmap_bpf__destroy
#endif

static volatile bool exiting = false;
static sigjmp_buf jmp;

int ifindex = -1;
const char *interface;
#if defined(XDP_DEVMAP)
int o_ifindex = -1;
const char *out_interface;
#endif

const char argp_prog_doc[] =
#if defined(XDP_BASIC)
	"USAGE: [-i <interface>]\n";
#elif defined(XDP_DEVMAP)
	"USAGE: [-i <interface>] [-o <interface>]\n";
#endif

static const struct argp_option opts[] = {
	{ "interface", 'i', "INTERFACE", 0, "Network interface to attach" },
#if defined(XDP_DEVMAP)
	{ "outinterface", 'o', "OUT-INTERFACE", 0, "Network interface to redirect" },
#endif
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
#if defined(XDP_DEVMAP)
	case 'o':
		out_interface = arg;
		o_ifindex = if_nametoindex(out_interface);
		if (!o_ifindex)
			o_ifindex = atoi(out_interface);
		break;
#endif
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
	siglongjmp(jmp, 1);
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
	sigsetjmp(jmp, 1);
	if (exiting)
		goto cleanup;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (ifindex == -1) {
		fprintf(stderr, "Need specify interface with -i\n");
		return -EINVAL;
	}
#if defined(XDP_DEVMAP)
	if (o_ifindex == -1) {
		fprintf(stderr, "Need specify out interface with -o\n");
		return -EINVAL;
	}
#endif

	skel = _bpf__open();
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

#if defined(XDP_BASIC)
	fprintf(stderr, "Track interface %s, index %d\n", interface, ifindex);
#elif defined(XDP_DEVMAP)
	fprintf(stderr, "Redirect %s(%d) to %s(%d)\n", interface, ifindex,
		out_interface, o_ifindex);
#endif
	fprintf(stderr, "Prog count %d\n", skel->skeleton->prog_cnt);

#if !defined(STRICT_SEC_NAME) && defined(XDP_BASIC)
	bpf_program__set_type(skel->progs.xdp_printk, BPF_PROG_TYPE_XDP);
# if defined(XDP_DEVMAP)
	bpf_program__set_type(skel->progs.xdp_devmap_printk, BPF_PROG_TYPE_XDP);
# endif
#endif

	err = _bpf__load(skel);
	if (err) {
		_bpf__destroy(skel);
		return 1;
	}

#if defined(XDP_BASIC)
	/* Attach BPF program to raw socket */
	prog_fd = bpf_program__fd(skel->progs.xdp_printk);

	err = tl_bpf_xdp_attach(ifindex, prog_fd, xdp_flags);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

#elif defined(XDP_DEVMAP) /* Test devmap */
	int map_fd, o_prog_fd;
	__u32 idx = 0;
	struct bpf_devmap_val val;

	prog_fd = bpf_program__fd(skel->progs.xdp_redir_prog);
	err = tl_bpf_xdp_attach(ifindex, prog_fd, XDP_FLAGS_SKB_MODE);
	if (err < 0) {
		printf("link set xdp fd failed\n");
		goto cleanup;
	}

	o_prog_fd = bpf_program__fd(skel->progs.xdp_devmap_printk);
	map_fd = bpf_map__fd(skel->maps.devmap_ports);

	val.ifindex = o_ifindex;
	val.bpf_prog.fd = o_prog_fd;

	err = bpf_map_update_elem(map_fd, &idx, &val, 0);
	if (err < 0) {
		printf("failed to update elem, err = %d, mapfd %d, progfd %d.\n",
			err, map_fd, o_prog_fd);
		goto cleanup;
	}
#else
# error "Must define XDP_BASIC or XDP_DEVMAP"
#endif

	/* Process events */
	read_trace_pipe();

cleanup:
	printf("Detach xdp from interface %s\n", interface);
	tl_bpf_xdp_detach(ifindex, xdp_flags);
#if defined(XDP_DEVMAP)
	printf("Detach xdp from out interface %s\n", out_interface);
	tl_bpf_xdp_detach(o_ifindex, xdp_flags);
#endif
	_bpf__destroy(skel);
	return 0;
}
