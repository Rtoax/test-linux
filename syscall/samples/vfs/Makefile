__USE_PROC_HELPERS__ = y

include helpers.mk

target-y := statfs
target-y += fstatfs

statfs-objs := ${PROC_HELPERS}

CFLAGS := -pthread

include main.mk
