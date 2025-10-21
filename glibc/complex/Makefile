target-y :=
target-y += _Complex_I _Complex __complex__
target-y += creal cimag
target-y += int
target-y += math

CC := gcc

CFLAGS ?=
CFLAGS += -Wno-error=unused-variable
CFLAGS += -pthread
# FIXME
CFLAGS += -Wno-unused-variable

LDFLAGS := -lm

include ../../template/main.mk

_Complex_I: _Complex_I.o
_Complex: _Complex.o
__complex__: __complex__.o
creal: creal.o
cimag: cimag.o
int: int.o
math: math.o
