#pragma once

#ifdef HAVE_HCCL
void hc_init(int dev_id);
#else
#define hc_init(id) do {} while (0)
#endif
