OUTPUT := .output/

target-y += parent-crash
target-y += thread

target-prog-y += orphan.sh
target-prog-y += orphan.sh.1

PROG_ARGS_orphan.sh := setsid
PROG_ARGS_orphan.sh.1 := bash
