// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

long alloc_buf_read_file(const char *filename, char **buf);
int open_secure_temp_file(void);

#ifdef __cplusplus
}
#endif
