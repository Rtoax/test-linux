#pragma once
#include <sys/resource.h>

void print_rlimit(const char *prefix, struct rlimit *rlimit);
void print_rusage(const struct rusage *rusage);
