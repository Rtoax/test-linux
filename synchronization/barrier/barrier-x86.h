#pragma once
#define barrier() __asm__ __volatile__("": : :"memory")

#if defined(__i386__)
#define smp_mb()	asm volatile("lock; addl $0,0(%%esp)" ::: "memory")
#define smp_rmb()	asm volatile("lock; addl $0,0(%%esp)" ::: "memory")
#define smp_wmb()	asm volatile("lock; addl $0,0(%%esp)" ::: "memory")
#define smp_rwmb()	smp_mb()
#elif defined(__x86_64__)
#define smp_mb() 	asm volatile("mfence":::"memory")
#define smp_rmb()	asm volatile("lfence":::"memory")
#define smp_wmb()	asm volatile("sfence" ::: "memory")
#define smp_rwmb()	smp_mb()
#endif
