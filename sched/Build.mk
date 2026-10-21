include kconfig.mk
include helpers.mk

subdir-y += kthread
subdir-y += reparent
subdir-y += scheduler
subdir-y += scripts
subdir-y += softlockup
subdir-y += waitqueue

target-y += current
target-y += uninterruptible
target-y += hung
target-y += zombie
target-y += stopped

zombie-objs := ${PROC_HELPERS}
