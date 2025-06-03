# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += fegetenv
TARGETS += feclearexcept
TARGETS += fegetround
TARGETS += feraiseexcept
TARGETS += fesetround
TARGETS += fetestexcept
TARGETS += demo-exception

CFLAGS := -Wall
CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -O0 -g

LDFLAGS := ${CFLAGS}

include ../../template/main.mk

fegetenv: fegetenv.o
feclearexcept: feclearexcept.o
fegetround: fegetround.o
feraiseexcept: feraiseexcept.o
fesetround: fesetround.o
fetestexcept: fetestexcept.o
demo-exception: demo-exception.o
