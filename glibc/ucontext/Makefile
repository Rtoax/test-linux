# SPDX-License-Identifier: GPL-3.0
targets :=
targets += swapcontext
targets += getcontext
targets += setcontext
targets += ucontext_t
targets += makecontext
targets += demo1

CFLAGS :=

CFLAGS_setcontext := -DTEST_SETCONTEXT=1

include ../../template/main.mk

swapcontext: swapcontext.o
getcontext: getcontext.o
setcontext: setcontext.o
ucontext_t: ucontext_t.o
makecontext: makecontext.o
demo1: demo1.o
