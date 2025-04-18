/* put addr to the Cache before use */
#ifndef prefetch
#define prefetch(x) __builtin_prefetch(x)
#endif

#ifndef prefetchw
#define prefetchw(x) __builtin_prefetch(x, 1)
#endif