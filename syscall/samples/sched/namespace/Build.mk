target-y += dummy dummy-fork dummy-vfork dummy-popen
target-y += setns
target-y += unshare unshare-execve

target-post-y := post0

dummy-fork-objs := fork_helpers.o
dummy-vfork-objs := fork_helpers.o
dummy-popen-objs := fork_helpers.o

CFLAGS := -D__USE_GNU
CFLAGS += -pthread

CFLAGS_dummy := -static
CFLAGS_dummy-fork := -static -DTRY_FORK=1
CFLAGS_dummy-vfork := -static -DTRY_VFORK=1
CFLAGS_dummy-popen := -static -DTRY_POPEN=1
