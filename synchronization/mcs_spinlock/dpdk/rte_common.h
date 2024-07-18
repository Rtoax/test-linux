#pragma once

/**
 * Force a function to be inlined
 */
#ifndef __rte_always_inline
#define __rte_always_inline inline __attribute__((always_inline))
#endif
/**
 * Force alignment
 */
#ifndef __rte_aligned
#define __rte_aligned(a) __attribute__((__aligned__(a)))
#endif

#define RTE_MAX_LCORE 4


/** C extension macro for environments lacking C11 features. */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define RTE_STD_C11 __extension__
#else
#define RTE_STD_C11
#endif
