// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <stdbool.h>

int open_raw_sock(const char *ifname, bool nonblk);
