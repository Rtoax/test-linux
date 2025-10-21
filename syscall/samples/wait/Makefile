target-y :=
target-y += waitpid
target-y += waitpid-sig
target-y += waitpid-kill
target-y += waitpid-status
target-y += wait

CFLAGS_waitpid-status := -DTEST_MAIN_WAITPID_STATUS=1

include ../../../template/main.mk

wait_helpers.o: wait_helpers.h
waitpid: waitpid.o
waitpid-sig: waitpid-sig.o
waitpid-kill: waitpid-kill.o
waitpid-status: waitpid-status.o wait_helpers.o
wait: wait.o
