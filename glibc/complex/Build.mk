target-y += _Complex_I
target-y += _Complex
target-y += __complex__
target-y += creal cimag
target-y += int
target-y += math

prog-y += ${target-y}

CFLAGS += -Wno-error=unused-variable
# FIXME
CFLAGS += -Wno-unused-variable

LDFLAGS := -lm
LDFLAGS += -pthread
