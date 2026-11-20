include json-c.mk
include helpers.mk

target-y += write
target-y += read
target-y += version

$(call target_link_helper,read,TLC_HELPERS)

CFLAGS += ${json-c-cflags}
LDFLAGS += ${json-c-ldflags}

prog-y += ${target-y}
