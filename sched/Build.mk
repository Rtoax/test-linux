__USE_PROC_HELPERS__ = y
__USE_SCHED_HELPERS__ = y

OUTPUT := .output/

include kconfig.mk
include helpers.mk

subdir-y += reparent
subdir-y += scripts

target-y += current
target-y += uninterruptible
target-y += hung
target-y += zombie
target-y += stopped
target-y += fifo
target-y += rr
target-y += deadline
target-$(CONFIG_SCHED_CLASS_EXT) += ext

zombie-objs := ${PROC_HELPERS}
fifo-objs := ${SCHED_HELPERS}
rr-objs := ${SCHED_HELPERS}
deadline-objs := ${SCHED_HELPERS}
ext-objs := ${SCHED_HELPERS}

CFLAGS_fifo := -DTEST_FIFO=1
CFLAGS_rr := -DTEST_RR=1
