include kconfig.mk
include helpers.mk

subdir-y += cfs
subdir-y += dl

target-y += fifo
target-y += rr
target-y += deadline
target-$(CONFIG_SCHED_CLASS_EXT) += ext

fifo-objs := ${SCHED_HELPERS}
rr-objs := ${SCHED_HELPERS}
deadline-objs := ${SCHED_HELPERS}
ext-objs := ${SCHED_HELPERS}

CFLAGS_fifo := -DTEST_FIFO=1
CFLAGS_rr := -DTEST_RR=1
