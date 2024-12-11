SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += mount
TARGETS += mount-tmpfs
TARGETS += fsmount
TARGETS += ramdisk

TARGETS_FS := fs.ext4

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -I../../libs/

build: ${TARGETS} ${TARGETS_FS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
mount: mount.o helpers.o
mount-tmpfs: mount-tmpfs.o
fsmount: fsmount.o helpers.o
ramdisk: ramdisk.o

fs.ext4:
	@echo -e "  MKFS  \033[1;32m$(@)\033[m"
	@./mkfs.sh
	@mkdir tmp-dir

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt fs.ext4
	@sudo umount tmp-dir || true
	${Q}rmdir tmp-dir || true
