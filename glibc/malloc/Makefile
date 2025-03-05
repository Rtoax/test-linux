# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

TARGETS :=
TARGETS += malloc overflow use-after-free double-free
TARGETS += mallinfo
TARGETS += mallopt
TARGETS += malloc_get_state
TARGETS += malloc_info
TARGETS += malloc_stats
TARGETS += posix_memalign
TARGETS += aligned_alloc
TARGETS += valloc
TARGETS += realloc
TARGETS += malloc_trim corrupted-size-vs.prev_size
TARGETS += malloc_usable_size
TARGETS += memalign
TARGETS += pvalloc

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

CFLAGS_mallinfo := -Wno-error=deprecated-declarations
CFLAGS_helpers := -Wno-error=deprecated-declarations
CFLAGS_aligned_alloc := -DALIGNED_ALLOC=1
CFLAGS_valloc := -DVALLOC=1
CFLAGS_overflow := -DOVERFLOW=1
CFLAGS_use-after-free := -DUSE_AFTER_FREE=1
CFLAGS_double-free := -DDOUBLE_FREE=1
CFLAGS_corrupted-size-vs.prev_size := -DCORRUPTED_SIZE_VS_PREV_SIZE=1

.PHONY: build
build: ${TARGETS}
	${Q}ld.so --list-tunables | grep -i malloc
	@echo -e " \033[1;33m Done \033[m"

malloc: malloc.o
overflow: overflow.o
use-after-free: use-after-free.o
double-free: double-free.o
mallinfo: mallinfo.o helpers.o
mallopt: mallopt.o
malloc_get_state: malloc_get_state.o
malloc_info: malloc_info.o
malloc_stats: malloc_stats.o
posix_memalign: posix_memalign.o
aligned_alloc: aligned_alloc.o
valloc: valloc.o
realloc: realloc.o
malloc_trim: malloc_trim.o helpers.o
corrupted-size-vs.prev_size: corrupted-size-vs.prev_size.o helpers.o
malloc_usable_size: malloc_usable_size.o
memalign: memalign.o
pvalloc: pvalloc.o


%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.xml
