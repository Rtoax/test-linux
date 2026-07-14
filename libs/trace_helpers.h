// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2024-2026 Rong Tao */
#pragma once
#include <stdarg.h>

int read_trace_pipe(void);
int read_trace_pipe_start(void);
int read_trace_pipe_wait(void);
int read_trace_pipe_stop(void);
