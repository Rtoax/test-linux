#pragma once

/**
 * Need vsock.ko, sudo modprobe vsock
 */
#define DEV_VSOCK	"/dev/vsock"

int vsock_get_local_cid(void);
