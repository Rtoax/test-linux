OUTPUT := .output/

target-y += parent-crash

target-shell-y += orphan.sh
target-shell-y += orphan.sh.1

SHELL_ARGS_orphan.sh := setsid
SHELL_ARGS_orphan.sh.1 := bash

include main.mk

parent-crash: ${OUTPUT}parent-crash.o
