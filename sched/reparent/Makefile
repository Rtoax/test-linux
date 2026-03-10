OUTPUT := .output/

target-y += parent-crash
target-y += thread

target-shell-y += orphan.sh
target-shell-y += orphan.sh.1

SHELL_ARGS_orphan.sh := setsid
SHELL_ARGS_orphan.sh.1 := bash

include main.mk
