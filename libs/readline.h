// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

ssize_t readline(int fd, void *vptr, size_t maxlen);

#ifdef __cplusplus
}
#endif
