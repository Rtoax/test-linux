LIBAIO_HDR := /usr/include/libaio.h

target-y :=
target-y += libaio
target-y += epoll

ifeq ($(wildcard $(LIBAIO_HDR)),)
  $(error "ERROR: Must install libaio development header")
endif

include cross-compile.mk

ifneq ($(wildcard $(LIBAIO_HDR)),)
  CFLAGS += -laio
  LDFLAGS += -laio
endif

include main.mk

libaio: libaio.o aio_helpers.o
epoll: epoll.o
