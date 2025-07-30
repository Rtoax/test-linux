// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#define gpu_init(dev_id)	cuda_init(dev_id)

void cuda_init(int dev_id);
void cuda_check_gpu_error(const char *msg);
const char *gpu_name(int dev_id, char *buf, int buf_len);
