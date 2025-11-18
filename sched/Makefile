__USE_PROC_HELPERS__ = y
__USE_SCHED_HELPERS__ = y

OUTPUT := .output/

target-y :=
target-y += current
target-y += uninterruptible
target-y += hung
target-y += zombie
target-y += stopped
target-y += deadline

include main.mk

current: ${OUTPUT}current.o
uninterruptible: ${OUTPUT}uninterruptible.o
hung: ${OUTPUT}hung.o
zombie: ${OUTPUT}zombie.o ${PROC_HELPERS}
stopped: ${OUTPUT}stopped.o
deadline: ${OUTPUT}deadline.o ${SCHED_HELPERS}
