// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

/**
 * Need vsock.ko, sudo modprobe vsock
 */
#define DEV_VSOCK	"/dev/vsock"

char *vsock_cid_name(unsigned int cid);
int vsock_get_local_cid(void);
unsigned int vsock_get_cid_from_args(int argc, char *argv[]);
