# SPDX-License-Identifier: GPL-3.0
targets :=
targets += setjmp
targets += sigsetjmp
targets += getline
targets += signal

CFLAGS :=

CFLAGS_sigsetjmp := -DSIGJMP=1
CFLAGS_setjmp := -DJMP=1

include ../../template/main.mk

setjmp: setjmp.o
sigsetjmp: sigsetjmp.o
getline: getline.o
signal: signal.o
