target-y += waitpid
target-y += waitpid-sig
target-y += waitpid-kill
target-y += waitpid-status
target-y += wait

waitpid-status-objs := wait_helpers.o

CFLAGS_waitpid-status := -DTEST_MAIN_WAITPID_STATUS=1
