# SPDX-License-Identifier: GPL-3.0
SHELL = bash

TARGETS :=
TARGETS += r-barrier
TARGETS += w-barrier
TARGETS += rw-barrier
TARGETS += no-barrier
TARGETS += __sync_synchronize
TARGETS += __atomic_thread_fence__ATOMIC_RELAXED
TARGETS += __atomic_thread_fence__ATOMIC_CONSUME
TARGETS += __atomic_thread_fence__ATOMIC_ACQUIRE
TARGETS += __atomic_thread_fence__ATOMIC_RELEASE
TARGETS += __atomic_thread_fence__ATOMIC_ACQ_REL
TARGETS += __atomic_thread_fence__ATOMIC_SEQ_CST
TARGETS += sequentially-consistent-waw
TARGETS += sequentially-consistent-waw-2
TARGETS += sequentially-consistent-raw

CC := gcc

CFLAGS := -Werror -Wall -pthread
CFLAGS += -I$(shell realpath .)/../../../synchronization/barrier/

CFLAGS_r-barrier := -DHAVE_MRBARRIER=1
CFLAGS_w-barrier := -DHAVE_MWBARRIER=1
CFLAGS_rw-barrier := -DHAVE_MRWBARRIER=1
CFLAGS_no-barrier := -DHAVE_NO_BARRIER=1
CFLAGS___sync_synchronize := -DHAVE___sync_synchronize=1
CFLAGS___atomic_thread_fence__ATOMIC_RELAXED := -DHAVE___atomic_thread_fence__ATOMIC_RELAXED=1
CFLAGS___atomic_thread_fence__ATOMIC_CONSUME := -DHAVE___atomic_thread_fence__ATOMIC_CONSUME=1
CFLAGS___atomic_thread_fence__ATOMIC_ACQUIRE := -DHAVE___atomic_thread_fence__ATOMIC_ACQUIRE=1
CFLAGS___atomic_thread_fence__ATOMIC_RELEASE := -DHAVE___atomic_thread_fence__ATOMIC_RELEASE=1
CFLAGS___atomic_thread_fence__ATOMIC_ACQ_REL := -DHAVE___atomic_thread_fence__ATOMIC_ACQ_REL=1
CFLAGS___atomic_thread_fence__ATOMIC_SEQ_CST := -DHAVE___atomic_thread_fence__ATOMIC_SEQ_CST=1
CFLAGS_sequentially-consistent-raw := ${CFLAGS_no-barrier}


build: ${TARGETS}

r-barrier: r-barrier.o
w-barrier: w-barrier.o
rw-barrier: rw-barrier.o
no-barrier: no-barrier.o
__sync_synchronize: __sync_synchronize.o
__atomic_thread_fence__ATOMIC_RELAXED: __atomic_thread_fence__ATOMIC_RELAXED.o
__atomic_thread_fence__ATOMIC_CONSUME: __atomic_thread_fence__ATOMIC_CONSUME.o
__atomic_thread_fence__ATOMIC_ACQUIRE: __atomic_thread_fence__ATOMIC_ACQUIRE.o
__atomic_thread_fence__ATOMIC_RELEASE: __atomic_thread_fence__ATOMIC_RELEASE.o
__atomic_thread_fence__ATOMIC_ACQ_REL: __atomic_thread_fence__ATOMIC_ACQ_REL.o
__atomic_thread_fence__ATOMIC_SEQ_CST: __atomic_thread_fence__ATOMIC_SEQ_CST.o
sequentially-consistent-waw: sequentially-consistent-waw.o
sequentially-consistent-waw-2: sequentially-consistent-waw-2.o
sequentially-consistent-raw: sequentially-consistent-raw.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f *.o ${TARGETS}
