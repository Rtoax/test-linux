#pragma once

int disable_oom(pid_t pid);
int get_oom_adj(pid_t pid);
int set_oom_adj(pid_t pid, int val);

