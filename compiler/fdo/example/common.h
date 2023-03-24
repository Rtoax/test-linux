#pragma once

#ifndef CACHE_LINE_SIZE
# error "You must define CACHE_LINE_SIZE=?"
#endif
#define __cacheline_size	CACHE_LINE_SIZE
#define __cacheline_align	__attribute__ ((aligned (__cacheline_size)))

void start(void);
void stop(void);
void swap_int(int *a, int *b);
