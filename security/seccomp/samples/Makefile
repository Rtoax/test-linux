target-y :=
target-y += mode_strict
target-y += mode_filter mode_filter-no-scmp
target-y += filter-write

CFLAGS_mode_filter-no-scmp := -DCONFIG_NO_SECCOMP=1

include ../../../template/main.mk

seccomp_helpers.o: seccomp_helpers.h

mode_strict: mode_strict.o seccomp_helpers.o
mode_filter: mode_filter.o
mode_filter-no-scmp: mode_filter-no-scmp.o
filter-write: filter-write.o
