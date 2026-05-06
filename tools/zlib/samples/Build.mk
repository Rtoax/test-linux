include helpers.mk

target-y += uncompress

LDFLAGS += -lz

$(call target_link_helper,uncompress,TLC_HELPERS)
