// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>

#include "libbpf_wrapper.h"


int tl_bpf_xdp_attach(int ifindex, int prog_fd, int xdp_flags)
{
	int err;
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
		printf("attach xdp fd %d to ifindex %d failed\n", prog_fd,
			ifindex);
	}

	return err;
}

/**
 * Like: sudo bpftool net detach xdp dev $interface
 */
int tl_bpf_xdp_detach(int ifindex, int xdp_flags)
{
	int err;
/**
 * libbpf commit e8802d6319ab ("libbpf: remove deprecated XDP APIs") remove
 * bpf_set_link_xdp_fd(), libbpf version v1.0.0
 */
#if LIBBPF_MAJOR_VERSION >= 1
	err = bpf_xdp_detach(ifindex, xdp_flags, NULL);
#else
	err = bpf_set_link_xdp_fd(ifindex, -1, xdp_flags);
#endif
	return err;
}
