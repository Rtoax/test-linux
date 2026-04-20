include json-c.mk

target-y += write
target-y += read

LDFLAGS += -ljson-c
