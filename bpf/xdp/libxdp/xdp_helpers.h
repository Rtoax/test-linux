// SPDX-License-Identifier: GPL-3.0
#pragma once

/**
 * see bcc examples/networking/xdp/xdp_redirect_map.py
 */
static inline void swap_src_dst_mac(void *data)
{
	unsigned short *p = data;
	unsigned short dst[3];
	dst[0] = p[0];
	dst[1] = p[1];
	dst[2] = p[2];
	p[0] = p[3];
	p[1] = p[4];
	p[2] = p[5];
	p[3] = dst[0];
	p[4] = dst[1];
	p[5] = dst[2];
}
