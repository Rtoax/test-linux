// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
#pragma once

typedef void *fd_handle_t;
struct fd_handler;

fd_handle_t fd_default_root(void);

struct fd_handler *register_fd(fd_handle_t *handle, int fd,
			       int (*handler)(int, void *), void *arg);
int unregister_fd(fd_handle_t *handle, int fd);
int handle_fd(fd_handle_t *handle, int fd);
void release_fd_handle(fd_handle_t *handle);
