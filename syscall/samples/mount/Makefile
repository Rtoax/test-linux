include ../../../template/kernel.mk

targets :=
targets += mount
targets += mount-tmpfs
ifeq ($(call kver_gt,5,1,0),y)
  targets += fsmount
endif
targets += ramdisk tmpfs

targets-prep := fs.ext4

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
	$(call log_tgt_exe,FS,,$(@))
	${Q}./mkfs.sh
	${Q}mkdir -p tmp-dir
