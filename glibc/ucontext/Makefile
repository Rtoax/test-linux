# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += swapcontext
TARGETS += getcontext
TARGETS += setcontext
TARGETS += ucontext_t
TARGETS += makecontext
TARGETS += demo1

CFLAGS := -Werror -Wall

CFLAGS_setcontext := -DTEST_SETCONTEXT=1

include ../../template/main.mk

swapcontext: swapcontext.o
getcontext: getcontext.o
setcontext: setcontext.o
ucontext_t: ucontext_t.o
makecontext: makecontext.o
demo1: demo1.o
