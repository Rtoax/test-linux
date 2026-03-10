# SPDX-License-Identifier: GPL-3.0
target-y += r-barrier
target-y += w-barrier
target-y += rw-barrier
target-y += no-barrier
target-y += __sync_synchronize
target-y += __atomic_thread_fence__ATOMIC_RELAXED
target-y += __atomic_thread_fence__ATOMIC_CONSUME
target-y += __atomic_thread_fence__ATOMIC_ACQUIRE
target-y += __atomic_thread_fence__ATOMIC_RELEASE
target-y += __atomic_thread_fence__ATOMIC_ACQ_REL
target-y += __atomic_thread_fence__ATOMIC_SEQ_CST
target-y += sequentially-consistent-waw
target-y += sequentially-consistent-waw-2
target-y += sequentially-consistent-raw
target-y += sequentially-consistent-war

LDFLAGS := -pthread
CFLAGS += -I$(shell realpath .)/../../../sync/barrier/

CFLAGS_r-barrier := -DHAVE_MRBARRIER=1
CFLAGS_w-barrier := -DHAVE_MWBARRIER=1
CFLAGS_rw-barrier := -DHAVE_MRWBARRIER=1
CFLAGS_no-barrier := -DHAVE_NO_BARRIER=1
CFLAGS___sync_synchronize := -DHAVE___sync_synchronize=1
CFLAGS___atomic_thread_fence__ATOMIC_RELAXED := -DHAVE_thread_fence__ATOMIC_RELAXED=1
CFLAGS___atomic_thread_fence__ATOMIC_CONSUME := -DHAVE_thread_fence__ATOMIC_CONSUME=1
CFLAGS___atomic_thread_fence__ATOMIC_ACQUIRE := -DHAVE_thread_fence__ATOMIC_ACQUIRE=1
CFLAGS___atomic_thread_fence__ATOMIC_RELEASE := -DHAVE_thread_fence__ATOMIC_RELEASE=1
CFLAGS___atomic_thread_fence__ATOMIC_ACQ_REL := -DHAVE_thread_fence__ATOMIC_ACQ_REL=1
CFLAGS___atomic_thread_fence__ATOMIC_SEQ_CST := -DHAVE_thread_fence__ATOMIC_SEQ_CST=1
CFLAGS_sequentially-consistent-raw := ${CFLAGS_no-barrier}
CFLAGS_sequentially-consistent-waw := -Wno-error=cpp
CFLAGS_sequentially-consistent-waw-2 := ${CFLAGS_sequentially-consistent-waw}

include main.mk
