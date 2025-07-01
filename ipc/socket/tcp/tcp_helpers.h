// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

void tcp_nodelay(int fd);
void tcp_cork(int fd);
void tcp_uncork(int fd);
