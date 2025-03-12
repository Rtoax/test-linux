#pragma once
#include <unistd.h>

void try_fork(void);
void try_popen(void);

void save_pid(const char *filename, pid_t pid);
int load_pid(const char *filename);
