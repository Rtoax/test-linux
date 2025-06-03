// SPDX-License-Identifier: GPL-3.0
/**
 * BPF_PROG_TYPE_SCHED_CLS
 *
 * As of kernel version v6.2 the only way to attach eBPF programs to TC is via
 * a netlink socket the details of which are complex. The usage of a netlink
 * library is recommended if you wish to manage attachment via an API.
 * However, the most common way to go about this is via the iproute2 tc CLI
 * tool which is the standard implementation for network utilities using the
 * netlink protocol.
 */
#include <argp.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <net/if.h>
#include <linux/bpf.h>
#include "btf_helpers.h"
#include "trace_helpers.h"
#include "libbpf_wrapper.h"
#if defined(TEST_SPIN_LOCK)
#include "spin_lock.h"
#include "spin_lock.skel.h"
#define struct_bpf	spin_lock_bpf
#define _bpf__open_and_load	spin_lock_bpf__open_and_load
#define _bpf__destroy	spin_lock_bpf__destroy
#elif defined(TEST_RBTREE)
#include "rbtree.h"
#include "spin_lock.h"
#include "rbtree.skel.h"
#define struct_bpf	rbtree_bpf
#define _bpf__open_and_load	rbtree_bpf__open_and_load
#define _bpf__destroy	rbtree_bpf__destroy
#else
#include "tc.skel.h"
#define struct_bpf	tc_bpf
#define _bpf__open_and_load	tc_bpf__open_and_load
#define _bpf__destroy	tc_bpf__destroy
#endif


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
		/* Try if not string. */
		if (!ifindex)
			ifindex = atoi(interface);

		if (ifindex == 0) {
			fprintf(stderr, "ERROR: not found interface %s.\n", interface);
			exit(EXIT_FAILURE);
		}
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

static void sig_int(int signo)
{
	read_trace_pipe_stop();
}

int main(int argc, char **argv)
{
	int err;
	bool hook_created = false;
	struct struct_bpf *skel;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if (ifindex == -1) {
		fprintf(stderr, "Need specify interface with -i\n");
		return -EINVAL;
	}

	DECLARE_LIBBPF_OPTS(bpf_tc_hook, tc_hook,
			.ifindex = ifindex,
			.attach_point = BPF_TC_INGRESS);
	DECLARE_LIBBPF_OPTS(bpf_tc_opts, tc_opts, .handle = 1, .priority = 1);

	if (signal(SIGINT, sig_int) == SIG_ERR) {
		err = errno;
		fprintf(stderr, "Can't set signal handler: %s\n", strerror(errno));
		goto cleanup;
	}

	libbpf_set_print(libbpf_print_fn);

	skel = _bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open BPF skeleton\n");
		return 1;
	}

#if defined(TEST_SPIN_LOCK) || defined(TEST_RBTREE)
	printf("spin_lock hash map max entries %d\n",
		bpf_map__max_entries(skel->maps.spin_lock_hash_map));

	int zero = 0;
	struct spin_lock_hmap_elem elem = {0};
	err = libbpf_bpf_map_update_elem(skel->maps.spin_lock_hash_map,
					&zero, sizeof(zero),
					&elem, sizeof(elem), 0);
	if (err) {
		fprintf(stderr, "Failed to update hash map: %d\n", err);
		goto cleanup;
	}

# if defined(TEST_RBTREE)
	struct rbtree_root rbroot = {};
	err = libbpf_bpf_map_update_elem(skel->maps.rbtree_root_map,
					&zero, sizeof(zero),
					&rbroot, sizeof(rbroot), BPF_EXIST);
	if (err) {
		fprintf(stderr, "Failed to update rbtree root hash map: %d\n", err);
		goto cleanup;
	}
# endif
#endif

	/**
	 * The hook (i.e. qdisc) may already exists because:
	 * 1. it is created by other processes or users
	 * 2. or since we are attaching to the TC ingress ONLY,
	 *    bpf_tc_hook_destroy does NOT really remove the qdisc,
	 *    there may be an egress filter on the qdisc
	 */
	err = bpf_tc_hook_create(&tc_hook);
	if (!err)
		hook_created = true;
	if (err && err != -EEXIST) {
		fprintf(stderr, "Failed to create TC hook: %d\n", err);
		goto cleanup;
	}

	tc_opts.prog_fd = bpf_program__fd(skel->progs.tc_ingress);
	err = bpf_tc_attach(&tc_hook, &tc_opts);
	if (err) {
		fprintf(stderr, "Failed to attach TC: %d\n", err);
		goto cleanup;
	}

	printf("Successfully started!\n");

	read_trace_pipe();

detach:
	/**
	 * like: sudo tc filter delete dev [lo] ingress
	 */
	tc_opts.flags = tc_opts.prog_fd = tc_opts.prog_id = 0;
	err = bpf_tc_detach(&tc_hook, &tc_opts);
	if (err) {
		fprintf(stderr, "Failed to detach TC: %d\n", err);
		goto cleanup;
	}

cleanup:
	printf("Goodbye!!\n");
	if (hook_created)
		bpf_tc_hook_destroy(&tc_hook);
	_bpf__destroy(skel);
	return -err;
}
