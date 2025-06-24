TARGETS :=
TARGETS += obstack
TARGETS += alloc-performance-cmp
TARGETS += multithread

CFLAGS :=
CFLAGS += -lpthread

LDFLAGS :=
LDFLAGS := -pthread

ifneq ($(wildcard /usr/include/jemalloc/jemalloc.h),)
  $(info Found jemalloc)
  CFLAGS += -DHAVE_JEMALLOC -ljemalloc
  LDFLAGS += -ljemalloc
endif

ifneq ($(wildcard /usr/include/gperftools/tcmalloc.h),)
  $(info Found tcmalloc)
  CFLAGS += -DHAVE_TCMALLOC -ltcmalloc
  LDFLAGS += -ltcmalloc
endif

include ../../template/main.mk

obstack: obstack.o
alloc-performance-cmp: alloc-performance-cmp.o
multithread:  multithread.o
