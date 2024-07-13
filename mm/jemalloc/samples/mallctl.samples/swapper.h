#include <jemalloc/jemalloc.h>
#ifndef mallctl
#undef mallctl
#define mallctl je_mallctl
#endif