TARGETS :=
TARGETS += mount
TARGETS += fsmount
TARGETS += ramdisk

TARGETS_FS := fs.ext4

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -I../../libs/

build: ${TARGETS} ${TARGETS_FS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

CFLAGS_ramdisk := -DTESTING=1

# Add more object.o file
mount: mount.o
fsmount: fsmount.o helpers.o
ramdisk: ramdisk.o

fs.ext4:
	./mkfs.sh
	mkdir tmp-dir

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt fs.ext4
	@umount tmp-dir || true
	@rmdir tmp-dir || true
