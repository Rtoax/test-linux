// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2024-2026 Rong Tao. All rights reserved. */
#pragma once
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int create_file(const char *filename, char ch, size_t bytes);
off_t file_seek_end(const char *filename);

#ifdef __cplusplus
}
#endif
