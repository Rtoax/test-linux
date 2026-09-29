// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
#pragma once

struct fd_handler;

struct fd_handler *register_fd(int fd, int (*handler)(int, void *), void *arg);
int unregister_fd(int fd);
int handle_fd(int fd);
void release_fd_handlers(void);
