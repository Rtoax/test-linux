#pragma once
#if defined(__x86_64__)
#include "cpuid-x86.h"
#elif defined(__aarch64__)
#include "cpuid-arm64.h"
#endif

int vendor_id(void);
int cpu_flags(void);

