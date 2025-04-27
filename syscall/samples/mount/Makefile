include ../../../tlbuild.mk
include ../../../kernel.mk

TARGETS :=
TARGETS += mount
TARGETS += mount-tmpfs
ifeq ($(call kernel_newer_than,5,1,0),y)
  TARGETS += fsmount
endif
TARGETS += ramdisk tmpfs

TARGETS_FS := fs.ext4

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -I../../libs/

build: ${TARGETS} ${TARGETS_FS}
	@echo -e " \033[1;33m Done \033[m"

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

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt fs.ext4
	${Q}sudo umount tmp-dir || true
	${Q}sudo umount tmpfs-* || true
	${Q}rmdir tmp-dir tmpfs-* || true
