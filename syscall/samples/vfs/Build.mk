include helpers.mk

target-y := statfs
target-y += fstatfs

statfs-objs := ${PROC_HELPERS}

LDFLAGS := -pthread
