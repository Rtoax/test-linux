targets :=
targets += fallocate
targets += open openat openat2
targets += splice splice-read
targets += O_ flags S_ mode

# F_ flags
targets += F_GET_SEALS
targets += F_ADD_SEALS
targets += F_SETLKW
targets += F_DUPFD
targets += F_GETFD
targets += F_GETFL
# O_ flags
targets += O_CLOEXEC
targets += O_PATH
targets += O_TMPFILE

CFLAGS :=

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
