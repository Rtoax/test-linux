TARGETS :=
TARGETS += addchild
TARGETS += parsexml
TARGETS += newformatxml
TARGETS += modifyxml

CC := gcc

LIBXML2_VERSION := libxml-2.0
LIBXML2_LIBS := $(shell pkg-config --libs libxml-2.0)
LIBXML2_CFLAGS := $(shell pkg-config --cflags libxml-2.0)

CFLAGS := -Werror -Wall
CFLAGS += $(LIBXML2_CFLAGS)
# FIXME: maybe use BAD_CAST
CFLAGS_addchild := -Wno-error=pointer-sign

LDFLAGS += $(LIBXML2_LIBS)

include ../../../template/main.mk

addchild: addchild.o
parsexml: parsexml.o
newformatxml: newformatxml.o
modifyxml: modifyxml.o
