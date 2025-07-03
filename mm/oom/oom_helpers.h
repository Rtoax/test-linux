// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#define KB 1024UL
#define MB (KB * 1024UL)
#define GB (MB * 1024UL)

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
