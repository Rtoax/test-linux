LIBAIO_HDR = /usr/include/libaio.h

TARGETS :=
TARGETS += libaio
TARGETS += epoll

ifeq ($(wildcard $(LIBAIO_HDR)),)
  $(error "ERROR: Must install libaio development header")
endif

LDFLAGS :=
CFLAGS += -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

include ../../../compiler/cross-compile.mk

ifneq ($(wildcard $(LIBAIO_HDR)),)
  CFLAGS += -laio
  LDFLAGS += -laio
endif

include ../../../template/main.mk

libaio: libaio.o aio_helpers.o
epoll: epoll.o
