// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once
#include <stdbool.h>

int socket_raw(const char *ifname, bool nonblk);
