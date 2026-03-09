LIBAIO_HDR := /usr/include/libaio.h

target-y += libaio
target-y += epoll

ifeq ($(wildcard $(LIBAIO_HDR)),)
  $(error "ERROR: Must install libaio development header")
endif

libaio-objs := aio_helpers.o

include cross-compile.mk

CFLAGS += -laio
LDFLAGS += -laio

include main.mk
