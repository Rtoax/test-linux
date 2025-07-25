JEMALLOC_HEADER=/usr/include/jemalloc/jemalloc.h

targets :=
targets += dallocx
targets += mallctl
targets += malloc_stats_print
targets += malloc_usable_size
targets += mallocx
targets += nallocx
targets += rallocx
targets += sallocx
targets += sdallocx
targets += xallocx
targets += stress

ifeq ($(wildcard $(JEMALLOC_HEADER)),)
  targets :=
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
