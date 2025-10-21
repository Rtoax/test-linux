CACHEFLUSH_HDR = /usr/include/asm/cacheflush.h

target-y :=
ifneq ($(wildcard $(CACHEFLUSH_HDR)),)
  target-y += cacheflush
endif

include ../../../template/main.mk

cacheflush: cacheflush.o
