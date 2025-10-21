OUTPUT := .output/

target-y :=
target-y += current
target-y += uninterruptible
target-y += hung
target-y += zombie
target-y += stopped

include ../template/main.mk

HELPERS := ${OUTPUT}proc_helpers.o

current: ${OUTPUT}current.o
uninterruptible: ${OUTPUT}uninterruptible.o
hung: ${OUTPUT}hung.o
zombie: ${OUTPUT}zombie.o ${HELPERS}
stopped: ${OUTPUT}stopped.o
