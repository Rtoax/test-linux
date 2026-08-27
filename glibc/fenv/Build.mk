# SPDX-License-Identifier: GPL-3.0
target-y += fegetenv
target-y += feclearexcept
target-y += fegetround
target-y += feraiseexcept
target-y += fesetround
target-y += fetestexcept
target-y += demo-exception

prog-y += ${target-y}

CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable

LDFLAGS += -lm
