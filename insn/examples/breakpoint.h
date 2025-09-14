#pragma once
/* Copyright (c) 2025 Rong Tao */
#if defined(__x86_64__) || defined(__i386__)
# define BREAKPOINT()	asm volatile("int3")
#elif defined(__aarch64__)
# define BREAKPOINT()	asm volatile("brk #0")
#endif
