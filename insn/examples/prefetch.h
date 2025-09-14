#ifndef _RTE_PREFETCH_X86_64_H_
#define _RTE_PREFETCH_X86_64_H_

#ifdef __cplusplus
extern "C" {
#endif

static inline void rte_prefetch0(const volatile void *p)
{
	asm volatile ("prefetcht0 %[p]" : : [p] "m" (*(const volatile char *)p));
}

static inline void rte_prefetch1(const volatile void *p)
{
	asm volatile ("prefetcht1 %[p]" : : [p] "m" (*(const volatile char *)p));
}

static inline void rte_prefetch2(const volatile void *p)
{
	asm volatile ("prefetcht2 %[p]" : : [p] "m" (*(const volatile char *)p));
}

static inline void rte_prefetch_non_temporal(const volatile void *p)
{
	asm volatile ("prefetchnta %[p]" : : [p] "m" (*(const volatile char *)p));
}

#ifdef __cplusplus
}
#endif

#endif /* _RTE_PREFETCH_X86_64_H_ */

