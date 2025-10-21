# SPDX-License-Identifier: GPL-3.0
include ../../compiler/compiler.mk

target-y :=
target-y += malloc overflow use-after-free double-free
target-y += mallinfo
target-y += mallopt
target-y += malloc_get_state
target-y += malloc_info
target-y += malloc_stats
target-y += posix_memalign
target-y += aligned_alloc
target-y += valloc
target-y += realloc
target-y += malloc_trim corrupted-size-vs.prev_size
target-y += malloc_usable_size
target-y += memalign
target-y += pvalloc

CC := gcc

CFLAGS :=

CFLAGS_mallinfo := -Wno-error=deprecated-declarations
CFLAGS_malloc_helpers := -Wno-error=deprecated-declarations
CFLAGS_aligned_alloc := -DALIGNED_ALLOC=1
CFLAGS_valloc := -DVALLOC=1
CFLAGS_overflow := -DOVERFLOW=1
CFLAGS_use-after-free := -DUSE_AFTER_FREE=1
CFLAGS_double-free := -DDOUBLE_FREE=1
CFLAGS_corrupted-size-vs.prev_size := -DCORRUPTED_SIZE_VS_PREV_SIZE=1

CC_-use-after-free := $(findstring 1,$(call check_compiler_option,$(CC),-Werror=use-after-free))
$(info CC_-use-after-free: ${CC_-use-after-free})
ifeq (${CC_-use-after-free},1)
  CFLAGS_use-after-free += -Wno-error=use-after-free
  CFLAGS_double-free += -Wno-error=use-after-free
endif

target-post-y := ld-list-tunables

include ../../template/main.mk

ld-list-tunables:
	${Q}ld.so --list-tunables 2>/dev/null | grep -i malloc || true

malloc_helpers.o: malloc_helpers.h

malloc: malloc.o
overflow: overflow.o
use-after-free: use-after-free.o
double-free: double-free.o
mallinfo: mallinfo.o malloc_helpers.o
mallopt: mallopt.o
malloc_get_state: malloc_get_state.o
malloc_info: malloc_info.o
malloc_stats: malloc_stats.o
posix_memalign: posix_memalign.o
aligned_alloc: aligned_alloc.o
valloc: valloc.o
realloc: realloc.o
malloc_trim: malloc_trim.o malloc_helpers.o
corrupted-size-vs.prev_size: corrupted-size-vs.prev_size.o malloc_helpers.o
malloc_usable_size: malloc_usable_size.o
memalign: memalign.o
pvalloc: pvalloc.o
