#pragma once

/**
 * Need vsock.ko, sudo modprobe vsock
 */
#define DEV_VSOCK	"/dev/vsock"

int vsock_get_local_cid(void);
unsigned int vsock_get_cid_from_args(int argc, char *argv[]);
