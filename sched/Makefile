__USE_PROC_HELPERS__ = y

OUTPUT := .output/

target-y :=
target-y += current
target-y += uninterruptible
target-y += hung
target-y += zombie
target-y += stopped

include ../template/main.mk

current: ${OUTPUT}current.o
uninterruptible: ${OUTPUT}uninterruptible.o
hung: ${OUTPUT}hung.o
zombie: ${OUTPUT}zombie.o ${PROC_HELPERS}
stopped: ${OUTPUT}stopped.o
