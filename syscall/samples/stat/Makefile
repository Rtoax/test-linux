
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

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
stat: stat.o
statx: statx.o
fstat: fstat.o
lstat: lstat.o
listdir: listdir.o
chmod: chmod.o
fchmod: fchmod.o
mkdir: mkdir.o
mknod: mknod.o
st_mode: st_mode.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(@)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -rf ${TARGETS} *.o *.d *.txt *.out
