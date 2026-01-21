// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

#ifndef __LUCA__
# error "Only support LUCA right now"
#endif

int main(int argc, char *argv[])
{
	lcVPUInst inst;
	lcVPUEncParamterType cfg;
	lcVpuFrameInfo input_frame, output_frame;

	lcInit(0);
	lcSetDevice(0);
	CUDA_RUNTIME_CHECK_EXIT(lcVpueOpen(&inst));

	memset(&cfg, 0, sizeof(lcVPUEncParamterType));
	memset(&input_frame, 0, sizeof(lcVpuFrameInfo));

	cfg.code_type = lcVpuH264;
	cfg.width = 1920;
	cfg.height = 1080;
	cfg.pixfmt = lcEncYuv420Planar;

	CUDA_RUNTIME_CHECK_EXIT(lcVpueCtrl(inst, lcSetEncAll, (void *)&cfg));

	CUDA_RUNTIME_CHECK_EXIT(lcVpueClose(inst));
	return 0;
}
