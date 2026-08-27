# SPDX-License-Identifier: GPL-3.0
target-y += swapcontext
target-y += getcontext
target-y += setcontext
target-y += ucontext_t
target-y += makecontext
target-y += demo1

prog-y += $(filter-out setcontext, ${target-y})

CFLAGS_setcontext := -DTEST_SETCONTEXT=1
