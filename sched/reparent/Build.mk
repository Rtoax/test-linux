target-y += parent-crash
target-y += thread

prog-y += orphan.sh
prog-y += orphan.sh.1

PROG_ARGS_orphan.sh := setsid
PROG_ARGS_orphan.sh.1 := bash
