# SPDX-License-Identifier: GPL-3.0
target-y += setjmp
target-y += sigsetjmp
target-y += getline
target-y += signal

prog-y += $(filter-out getline signal, ${target-y})

CFLAGS_sigsetjmp := -DSIGJMP=1
CFLAGS_setjmp := -DJMP=1
