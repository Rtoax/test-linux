SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

TARGETS :=
TARGETS += fallocate
TARGETS += open openat openat2
TARGETS += splice splice-read
TARGETS += O_ flags S_ mode

# F_ flags
TARGETS += F_GET_SEALS
TARGETS += F_ADD_SEALS
TARGETS += F_SETLKW
TARGETS += F_DUPFD
TARGETS += F_GETFD
TARGETS += F_GETFL
# O_ flags
TARGETS += O_CLOEXEC
TARGETS += O_PATH
TARGETS += O_TMPFILE

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
fallocate: fallocate.o
open: open.o helpers.o
openat: openat.o helpers.o
openat2: openat2.o helpers.o
splice: splice.o
splice-read: splice-read.o
O_: O_.o
flags: flags.o
S_: S_.o
mode: mode.o

F_GET_SEALS: F_GET_SEALS.o
F_ADD_SEALS: F_ADD_SEALS.o
F_SETLKW: F_SETLKW.o
F_DUPFD: F_DUPFD.o
F_GETFD: F_GETFD.o
F_GETFL: F_GETFL.o

O_CLOEXEC: O_CLOEXEC.o
O_PATH: O_PATH.o
O_TMPFILE: O_TMPFILE.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	${Q}./fallocate.test.sh
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt *.dat
