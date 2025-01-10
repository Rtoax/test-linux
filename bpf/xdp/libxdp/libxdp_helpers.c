#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <setjmp.h>
#include <net/if.h>
#include <unistd.h>

#include "libxdp_helpers.h"


/**
 * When XDP_USE_NEED_WAKEUP is set, the consuming of the FILL ring buffer must
 * be triggered by a recvfrom syscall.
 *
 * see linux:tools/testing/selftests/bpf/xskxceiver.c
 */
int kick_rx(int xdp_fd)
{
	int err;
	err = recvfrom(xdp_fd, NULL, 0, MSG_DONTWAIT, NULL, NULL);
	if (err < 0) {
		fprintf(stderr, "Trigger FILL ring buffer failed.\n");
		return err;
	}
	return 0;
}


/**
 * Also, when XDP_USE_NEED_WAKEUP is set, the sending of packets queued in the
 * TX buffer only happens when triggered by the sendto syscall like so:
 *
 * see linux:tools/testing/selftests/bpf/xskxceiver.c
 */
void kick_tx(int xdp_fd)
{
	int ret;

	ret = sendto(xdp_fd, NULL, 0, MSG_DONTWAIT, NULL, 0);
	if (ret >= 0)
		return;
	if (errno == ENOBUFS || errno == EAGAIN || errno == EBUSY || errno == ENETDOWN) {
		usleep(100);
		return;
	}
	fprintf(stderr, "kick_tx %m\n");
}

/**
 * See structure xsk_ring_prod and xsk_ring_cons
 */
struct xsk_ring {
	__u32 cached_prod;
	__u32 cached_cons;
	__u32 mask;
	__u32 size;
	__u32 *producer;
	__u32 *consumer;
	void *ring;
	__u32 *flags;
};

void display_xsk_ring(const char *pfx, void *ring)
{
	struct xsk_ring *r = ring;

	printf("%s: cached_prod:%d, cached_cons:%d, mask:0x%x, size:%d,"
	       " producer:%d(%p), consumer:%d(%p)\n",
		pfx,
		r->cached_prod, r->cached_cons,
		r->mask, r->size,
		*r->producer, r->producer,
		*r->consumer, r->consumer);
}

struct list_head {
	struct list_head *next, *prev;
};

/**
 * Only in kernel, user space just use 'struct xsk_umem *'.
 */
struct xsk_umem {
	struct xsk_ring_prod *fill_save;
	struct xsk_ring_cons *comp_save;
	char *umem_area;
	struct xsk_umem_config config;
	int fd;
	int refcount;
	struct list_head ctx_list;
};

void display_xsk_umem(const char *pfx, struct xsk_umem *umem)
{
	char pfx_ring[128];
	if (umem->fill_save) {
		sprintf(pfx_ring, "%s: fill", pfx);
		display_xsk_ring(pfx_ring, umem->fill_save);
	}
	if (umem->comp_save) {
		sprintf(pfx_ring, "%s: comp", pfx);
		display_xsk_ring(pfx_ring, umem->comp_save);
	}
	printf("%s: umem_area %p\n", pfx, umem->umem_area);
	printf("%s: fd %d\n", pfx, umem->fd);
	printf("%s: refcount %d\n", pfx, umem->refcount);
}
