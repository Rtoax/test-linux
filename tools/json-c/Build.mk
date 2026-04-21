include json-c.mk
include helpers.mk

target-y += write
target-y += read

$(call target_link_helper,read,TLC_HELPERS)

LDFLAGS += -ljson-c
