// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

void gpu_init(int dev_id);
void gpu_check_gpu_error(const char *msg);
const char *gpu_name(int dev_id, char *buf, int buf_len);
