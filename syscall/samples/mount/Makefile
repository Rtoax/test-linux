include ../../../kernel.mk

TARGETS :=
TARGETS += mount
TARGETS += mount-tmpfs
ifeq ($(call kernel_newer_than,5,1,0),y)
  TARGETS += fsmount
endif
TARGETS += ramdisk tmpfs

TARGETS_PREP := fs.ext4

CFLAGS :=
CFLAGS += -pthread
CFLAGS += -I../../libs/

include ../../../template/main.mk

mnt_helpers.o: mnt_helpers.h
mount.o: mnt_helpers.h
fsmount.o: mnt_helpers.h

tmpfs_helpers.o: tmpfs_helpers.h

mount: mount.o mnt_helpers.o
mount-tmpfs: mount-tmpfs.o
fsmount: fsmount.o mnt_helpers.o
ramdisk: ramdisk.o tmpfs_helpers.o
tmpfs: tmpfs.o tmpfs_helpers.o

fs.ext4:
	@echo -e "  MKFS  \033[1;32m$(@)\033[m"
	${Q}./mkfs.sh
	${Q}mkdir tmp-dir
