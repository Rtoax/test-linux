#pragma once
#include <unistd.h>

void try_fork(int vf, char *argv[]);
void try_popen(char *cmd_buf);

void save_pid(const char *filename, pid_t pid);
int load_pid(const char *filename);
