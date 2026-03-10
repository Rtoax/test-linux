target-y += addchild
target-y += parsexml
target-y += newformatxml
target-y += modifyxml

LIBXML2_VERSION := libxml-2.0
LIBXML2_LIBS := $(shell pkg-config --libs libxml-2.0)
LIBXML2_CFLAGS := $(shell pkg-config --cflags libxml-2.0)

CFLAGS += $(LIBXML2_CFLAGS)
# FIXME: maybe use BAD_CAST
CFLAGS_addchild := -Wno-error=pointer-sign

LDFLAGS += $(LIBXML2_LIBS)

include main.mk
