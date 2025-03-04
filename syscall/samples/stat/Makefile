include ../../../tlbuild.mk

TARGETS := lstat
TARGETS += stat
TARGETS += statx
TARGETS += fstat
TARGETS += listdir
TARGETS += chmod
TARGETS += fchmod
TARGETS += mkdir
TARGETS += mknod
TARGETS += st_mode
TARGETS += fstatat
TARGETS += utimensat

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

stat: stat.o helpers.o
statx: statx.o
fstat: fstat.o helpers.o
lstat: lstat.o helpers.o
listdir: listdir.o
chmod: chmod.o
fchmod: fchmod.o
mkdir: mkdir.o
mknod: mknod.o
fstatat: fstatat.o helpers.o
st_mode: st_mode.o helpers.o
utimensat: utimensat.o

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
	${Q}rm -rf ${TARGETS} *.o *.d *.txt *.out
