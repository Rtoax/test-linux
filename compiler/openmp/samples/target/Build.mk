# SPDX-License-Identifier: GPL-3.0
target-y += target

prog-y += ${target-y}

CFLAGS += -Wno-error=unused-variable
CFLAGS +=  -fopenmp
LDFLAGS += -fopenmp
