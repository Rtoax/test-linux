// SPDX-License-Identifier: GPL-3.0
#pragma once
#include <stdarg.h>
#include <bpf/libbpf.h>

int read_trace_pipe(void);
int read_trace_pipe_start(void);
int read_trace_pipe_wait(void);
int read_trace_pipe_stop(void);

int print_bpf_log_buf(char *buf, size_t size);

int libbpf_print_fn(enum libbpf_print_level level, const char *format,
		    va_list args);
