# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += setjmp
TARGETS += sigsetjmp
TARGETS += getline
TARGETS += signal

CFLAGS := -Werror -Wall
CFLAGS += -D_GNU_SOURCE

CFLAGS_sigsetjmp := -DSIGJMP=1
CFLAGS_setjmp := -DJMP=1

include ../../template/main.mk

setjmp: setjmp.o
sigsetjmp: sigsetjmp.o
getline: getline.o
signal: signal.o
