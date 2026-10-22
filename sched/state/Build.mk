include helpers.mk

target-y += uninterruptible
target-y += hung
target-y += zombie
target-y += stopped

zombie-objs := ${PROC_HELPERS}
