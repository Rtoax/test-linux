__USE_PROC_HELPERS__ = y
__USE_SCHED_HELPERS__ = y

OUTPUT := .output/

include kconfig.mk

target-y :=
target-y += current
target-y += uninterruptible
target-y += hung
target-y += zombie
target-y += stopped
target-y += fifo
target-y += rr
target-y += deadline
target-$(CONFIG_SCHED_CLASS_EXT) += ext

CFLAGS_fifo := -DTEST_FIFO=1
CFLAGS_rr := -DTEST_RR=1

include main.mk

current: ${OUTPUT}current.o
uninterruptible: ${OUTPUT}uninterruptible.o
hung: ${OUTPUT}hung.o
zombie: ${OUTPUT}zombie.o ${PROC_HELPERS}
stopped: ${OUTPUT}stopped.o
fifo: ${OUTPUT}fifo.o ${SCHED_HELPERS}
rr: ${OUTPUT}rr.o ${SCHED_HELPERS}
deadline: ${OUTPUT}deadline.o ${SCHED_HELPERS}
ext: ${OUTPUT}ext.o ${SCHED_HELPERS}
