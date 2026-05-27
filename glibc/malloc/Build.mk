# SPDX-License-Identifier: GPL-3.0
include compiler.mk

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

prog-y := list-tunables.sh

mallinfo-objs := malloc_helpers.o
malloc_trim-objs := malloc_helpers.o
corrupted-size-vs.prev_size-objs := malloc_helpers.o

CFLAGS_mallinfo := -Wno-error=deprecated-declarations
CFLAGS_malloc_helpers := -Wno-error=deprecated-declarations
CFLAGS_aligned_alloc := -DALIGNED_ALLOC=1
CFLAGS_valloc := -DVALLOC=1
CFLAGS_overflow := -DOVERFLOW=1
CFLAGS_use-after-free := -DUSE_AFTER_FREE=1
CFLAGS_double-free := -DDOUBLE_FREE=1
CFLAGS_corrupted-size-vs.prev_size := -DCORRUPTED_SIZE_VS_PREV_SIZE=1

CC_-use-after-free := $(findstring y,$(call compiler_support_option,$(CC),-Werror=use-after-free))
$(info CC_-use-after-free: ${CC_-use-after-free})
ifeq (${CC_-use-after-free},y)
  CFLAGS_use-after-free += -Wno-error=use-after-free
  CFLAGS_double-free += -Wno-error=use-after-free
endif
