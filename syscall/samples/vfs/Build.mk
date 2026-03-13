include helpers.mk

target-y := statfs
target-y += fstatfs

statfs-objs := ${PROC_HELPERS}

CFLAGS := -pthread
