// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#define KB 1024UL
#define MB (KB * 1024UL)
#define GB (MB * 1024UL)

/*
 * /proc/<pid>/oom_score_adj set to OOM_SCORE_ADJ_MIN disables oom killing for
 * pid.
 */
#define OOM_SCORE_ADJ_MIN	(-1000)
#define OOM_SCORE_ADJ_MAX	1000

/*
 * /proc/<pid>/oom_adj set to -17 protects from the oom killer for legacy
 * purposes.
 */
#define OOM_DISABLE (-17)

/* inclusive(包容性) */
#define OOM_ADJUST_MIN (-16)
#define OOM_ADJUST_MAX 15

int disable_oom_by_adj(pid_t pid);
int get_oom_adj(pid_t pid);
int set_oom_adj(pid_t pid, int val);

int get_oom_score(pid_t pid);

int disable_oom_by_score_adj(pid_t pid);
int set_oom_score_adj(pid_t pid, int val);
int get_oom_score_adj(pid_t pid);

unsigned long str2size(const char *str);

unsigned long totalram(void);
unsigned long freeram(void);
unsigned long totalswap(void);
unsigned long freeswap(void);
