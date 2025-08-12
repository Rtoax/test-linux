// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#define UNSOCKET_PATH   "/tmp/fd-pass.socket"
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)

int sock_send_fds(int socket, int *fds, int n);
int sock_recv_fds(int socket, int *fds, int n);
