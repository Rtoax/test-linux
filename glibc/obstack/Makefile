SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += obstack
TARGETS += alloc-performance-cmp
TARGETS += multithread

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -lpthread

LDFLAGS :=
LDLIBS :=

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


.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

obstack: obstack.o
alloc-performance-cmp: alloc-performance-cmp.o
multithread:  multithread.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
