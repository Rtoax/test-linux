#pragma once
#include <sys/resource.h>

void print_rlimit(const char *prefix, struct rlimit *rlimit);
void print_rusage(const char *prefix, const struct rusage *rusage);
