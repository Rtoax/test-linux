target-y += _Complex_I _Complex __complex__
target-y += creal cimag
target-y += int
target-y += math

CFLAGS += -Wno-error=unused-variable
# FIXME
CFLAGS += -Wno-unused-variable

LDFLAGS := -lm
LDFLAGS += -pthread

include main.mk
