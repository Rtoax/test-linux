include kernel.mk

target-y += mount
target-y += mount-tmpfs
ifeq ($(call kver_gt,5,1,0),y)
  target-y += fsmount
endif
target-y += ramdisk tmpfs

mount-objs := mnt_helpers.o
fsmount-objs := mnt_helpers.o
ramdisk-objs := tmpfs_helpers.o
tmpfs-objs := tmpfs_helpers.o

prep-y := fs.ext4

CFLAGS += -pthread
CFLAGS += -I../../libs/
