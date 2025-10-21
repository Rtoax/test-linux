target-y :=
target-y += dummy dummy-fork dummy-vfork dummy-popen
target-y += setns
target-y += unshare unshare-execve

CFLAGS := -D__USE_GNU
CFLAGS += -pthread

CFLAGS_dummy := -static
CFLAGS_dummy-fork := -static -DTRY_FORK=1
CFLAGS_dummy-vfork := -static -DTRY_VFORK=1
CFLAGS_dummy-popen := -static -DTRY_POPEN=1

target-test-y := test0

include ../../../../template/main.mk

fork_helpers.o: fork_helpers.h

dummy: dummy.o
dummy-fork: dummy-fork.o fork_helpers.o
dummy-vfork: dummy-vfork.o fork_helpers.o
dummy-popen: dummy-popen.o fork_helpers.o
setns: setns.o
unshare: unshare.o
unshare-execve: unshare-execve.o

test0:
	${Q}timeout --signal=SIGINT 4 ./fork-ENOMEM.sh test3 || true

