#pragma once

#ifndef CACHE_LINE_SIZE
# error "You must define CACHE_LINE_SIZE=?"
#endif
#define __cacheline_size	CACHE_LINE_SIZE

#if defined(CACHELINE_ALIGN)
# define __cacheline_align	__attribute__ ((aligned (__cacheline_size)))
#else
# warning "Not define CACHELINE_ALIGN"
# define __cacheline_align
#endif

#if defined(NOINLINE)
# define __noinline	__attribute__ ((noinline))
#else
# warning "Not define NOINLINE"
# define __noinline
#endif

#define __attr __cacheline_align __noinline


#define FN(f)	__attr fdo_test_##f

void FN(start)(void);
void FN(stop)(void);
void FN(swap_int)(int *a, int *b);
