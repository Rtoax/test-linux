LIBAIO_HDR := /usr/include/libaio.h

targets :=
targets += libaio
targets += epoll

ifeq ($(wildcard $(LIBAIO_HDR)),)
  $(error "ERROR: Must install libaio development header")
endif

include ../../../compiler/cross-compile.mk

ifneq ($(wildcard $(LIBAIO_HDR)),)
  CFLAGS += -laio
  LDFLAGS += -laio
endif

include ../../../template/main.mk

libaio: libaio.o aio_helpers.o
epoll: epoll.o
