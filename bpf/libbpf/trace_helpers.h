// SPDX-License-Identifier: GPL-3.0
#pragma once

int read_trace_pipe_cb(int (*cb)(const char *str, void *arg), void *arg);
int read_trace_pipe(void);
