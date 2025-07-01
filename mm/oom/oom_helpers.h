// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

int disable_oom_by_adj(pid_t pid);
int get_oom_adj(pid_t pid);
int set_oom_adj(pid_t pid, int val);

int get_oom_score(pid_t pid);

int disable_oom_by_score_adj(pid_t pid);
int set_oom_score_adj(pid_t pid, int val);
int get_oom_score_adj(pid_t pid);
