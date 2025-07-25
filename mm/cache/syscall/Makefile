CACHEFLUSH_HDR = /usr/include/asm/cacheflush.h

targets :=
ifneq ($(wildcard $(CACHEFLUSH_HDR)),)
  targets += cacheflush
endif

include ../../../template/main.mk

cacheflush: cacheflush.o
