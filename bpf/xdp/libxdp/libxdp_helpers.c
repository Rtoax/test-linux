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

