#pragma once

#if defined(__aarch64__)
#define smp_rmb()	asm volatile("dmb ishld" : : : "memory")
#define smp_wmb()	asm volatile("dmb ishst" : : : "memory")
#define smp_mb()	asm volatile("dmb ish" : : : "memory")
#define smp_rwmb()	smp_mb()
#elif defined(__arm__)
/* These are only valid for armv7 and above */
#define smp_rmb()	asm volatile("dmb ish" : : : "memory")
#define smp_wmb()	asm volatile("dmb ishst" : : : "memory")
#define smp_mb()	asm volatile("dmb ish" : : : "memory")
#define smp_rwmb()	smp_mb()
#endif
