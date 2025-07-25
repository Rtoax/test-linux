targets :=
targets += waitpid
targets += waitpid-sig
targets += waitpid-kill
targets += waitpid-status
targets += wait

CFLAGS_waitpid-status := -DTEST_MAIN_WAITPID_STATUS=1

include ../../../template/main.mk

wait_helpers.o: wait_helpers.h
waitpid: waitpid.o
waitpid-sig: waitpid-sig.o
waitpid-kill: waitpid-kill.o
waitpid-status: waitpid-status.o wait_helpers.o
wait: wait.o
