include jemalloc.mk

target-y += obstack
target-y += alloc-performance-cmp
target-y += multithread

LDFLAGS := -pthread

CFLAGS += ${jemalloc-cflags}
LDFLAGS += ${jemalloc-ldflags}

ifneq ($(wildcard /usr/include/gperftools/tcmalloc.h),)
  $(info Found tcmalloc)
  CFLAGS += -DHAVE_TCMALLOC -ltcmalloc
  LDFLAGS += -ltcmalloc
endif
