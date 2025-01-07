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
