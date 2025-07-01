// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <sys/types.h>

int create_file(const char *filename, char ch, size_t bytes);
off_t file_seek_end(const char *filename);
