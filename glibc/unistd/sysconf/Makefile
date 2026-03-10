target-y := NPROCESSORS
target-y += PAGESIZE
target-y += sysconf

CFLAGS_NPROCESSORS := -D_NPROCESSORS=1
CFLAGS_sysconf := -Wno-error

target-prep-y := confs_def.h
target-clean-y := cleans

include main.mk

confs_def.h: sysconf.sh
	$(shell bash sysconf.sh)

cleans:
	${Q}rm -f gen-sysconf-* confs_def.h
