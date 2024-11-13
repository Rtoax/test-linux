#pragma once

#if defined(__aarch64__) || defined(__arm__)
#include "barrier-arm.h"
#elif defined(__x86_64__) || defined(__i386__)
#include "barrier-x86.h"
#elif defined(__sw_64__)
#include "barrier-sw64.h"
#elif defined(__riscv)
#include "barrier-riscv.h"
#else
# error "Not support cpu architecture"
#endif
