# SPDX-License-Identifier: GPL-3.0
target-y += fegetenv
target-y += feclearexcept
target-y += fegetround
target-y += feraiseexcept
target-y += fesetround
target-y += fetestexcept
target-y += demo-exception

CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable
CFLAGS += -I../../../
CFLAGS += -O0 -g

LDFLAGS += -lm

include main.mk
