SHELL = bash
include ../../../tlbuild.mk


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

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -ljemalloc

LDFLAGS :=

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
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

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o *.d
