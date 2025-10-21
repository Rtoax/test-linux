# SPDX-License-Identifier: GPL-3.0
target-y :=
target-y += fegetenv
target-y += feclearexcept
target-y += fegetround
target-y += feraiseexcept
target-y += fesetround
target-y += fetestexcept
target-y += demo-exception

CFLAGS :=
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
