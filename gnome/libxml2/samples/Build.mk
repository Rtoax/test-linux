include libxml2.mk

target-y += addchild
target-y += parsexml
target-y += newformatxml
target-y += modifyxml

CFLAGS += $(LIBXML2_CFLAGS)
LDFLAGS += $(LIBXML2_LIBS)

# FIXME: maybe use BAD_CAST
CFLAGS_addchild := -Wno-error=pointer-sign
