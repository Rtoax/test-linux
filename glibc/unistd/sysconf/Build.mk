target-y := NPROCESSORS
target-y += PAGESIZE
target-y += sysconf

target-prep-y := confs_def.h
target-clean-y := cleans

CFLAGS_NPROCESSORS := -D_NPROCESSORS=1
CFLAGS_sysconf := -Wno-error
