#pragma once

#define gpu_init(dev_id)	cuda_init(dev_id)

void cuda_init(int dev_id);
void cuda_check_gpu_error(const char *msg);
