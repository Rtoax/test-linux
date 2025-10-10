OUTPUT := .output/

targets :=
targets += current
targets += uninterruptible
targets += hung
targets += zombie
targets += stopped

include ../template/main.mk

HELPERS := ${OUTPUT}proc_helpers.o

current: ${OUTPUT}current.o
uninterruptible: ${OUTPUT}uninterruptible.o
hung: ${OUTPUT}hung.o
zombie: ${OUTPUT}zombie.o ${HELPERS}
stopped: ${OUTPUT}stopped.o
