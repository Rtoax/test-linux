target-y += mode_strict
target-y += mode_filter mode_filter-no-scmp
target-y += filter-write

mode_strict-objs := seccomp_helpers.o

CFLAGS_mode_filter-no-scmp := -DCONFIG_NO_SECCOMP=1

include main.mk
