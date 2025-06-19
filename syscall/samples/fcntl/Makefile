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

CFLAGS := -Werror -Wall -D_GNU_SOURCE

include ../../../template/main.mk

fcntl_helpers.o: fcntl_helpers.h
fallocate: fallocate.o
open: open.o fcntl_helpers.o
openat: openat.o fcntl_helpers.o
openat2: openat2.o fcntl_helpers.o
splice: splice.o
splice-read: splice-read.o
O_: O_.o
O_.o: O_.h
flags: flags.o
S_: S_.o
mode: mode.o

F_GET_SEALS: F_GET_SEALS.o
F_ADD_SEALS: F_ADD_SEALS.o
F_SETLKW: F_SETLKW.o fcntl_helpers.o
F_DUPFD: F_DUPFD.o
F_GETFD: F_GETFD.o
F_GETFL: F_GETFL.o

O_CLOEXEC: O_CLOEXEC.o
O_PATH: O_PATH.o
O_TMPFILE: O_TMPFILE.o
