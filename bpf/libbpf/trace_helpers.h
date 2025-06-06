// SPDX-License-Identifier: GPL-3.0
#pragma once
#include <stdarg.h>
#include <bpf/libbpf.h>

int read_trace_pipe(void);
int read_trace_pipe_start(void);
int read_trace_pipe_wait(void);
int read_trace_pipe_stop(void);
