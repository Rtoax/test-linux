JEMALLOC_HEADER=/usr/include/jemalloc/jemalloc.h

target-y :=
target-y += dallocx
target-y += mallctl
target-y += malloc_stats_print
target-y += malloc_usable_size
target-y += mallocx
target-y += nallocx
target-y += rallocx
target-y += sallocx
target-y += sdallocx
target-y += xallocx
target-y += stress

ifeq ($(wildcard $(JEMALLOC_HEADER)),)
  target-y :=
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
