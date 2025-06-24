CACHEFLUSH_HDR = /usr/include/asm/cacheflush.h

TARGETS :=
ifneq ($(wildcard $(CACHEFLUSH_HDR)),)
  TARGETS += cacheflush
endif

include ../../../template/main.mk

cacheflush: cacheflush.o
