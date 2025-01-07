#pragma once
#include <bpf/bpf.h>
#include <bpf/libbpf.h>

/**
 * libbpf commit b78c75fcb347 ("Makefile: remove xsk.c and xsk.h") v1.0 remove
 * xsk.{c,h}, use libxdp instead.
 */
#if LIBBPF_MAJOR_VERSION < 1
#include <bpf/xsk.h>
#else
#include <xdp/xsk.h>
#endif

int kick_rx(int xdp_fd);
void kick_tx(int xdp_fd);
