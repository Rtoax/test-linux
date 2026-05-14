include kconfig.mk
include helpers.mk

subdir-y += kthread
subdir-y += reparent
subdir-y += scripts
subdir-y += softlockup
subdir-y += waitqueue

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
