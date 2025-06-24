JEMALLOC_HEADER=/usr/include/jemalloc/jemalloc.h

TARGETS :=
TARGETS += dallocx
TARGETS += mallctl
TARGETS += malloc_stats_print
TARGETS += malloc_usable_size
TARGETS += mallocx
TARGETS += nallocx
TARGETS += rallocx
TARGETS += sallocx
TARGETS += sdallocx
TARGETS += xallocx
TARGETS += stress

ifeq ($(wildcard $(JEMALLOC_HEADER)),)
  TARGETS :=
  $(warning "WARNING: Maybe install jemalloc development package")
endif

LDFLAGS += -ljemalloc

include ../../../template/main.mk

dallocx: dallocx.o
mallctl: mallctl.o
malloc_stats_print: malloc_stats_print.o
malloc_usable_size: malloc_usable_size.o
mallocx: mallocx.o
nallocx: nallocx.o
rallocx: rallocx.o
sallocx: sallocx.o
sdallocx: sdallocx.o
xallocx: xallocx.o
stress: stress.o
