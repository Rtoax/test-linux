include ../../../../tlbuild.mk

include ../../../../kconfig.mk

TARGETS :=
TARGETS += msync
TARGETS += fexecve
TARGETS += mmap-anon
TARGETS += mmap-file mremap-file
TARGETS += remap_file_pages
TARGETS += get_unmapped_page
TARGETS += mmap-multi-thread-copy
TARGETS += mmap-exec

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

DEBUG := yes
CC := gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -lrt

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

CFLAGS_mremap-file := -DMREMAP=1

ifeq ($(CONFIG_ANON_VMA_NAME),y)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

# mmap-exec never should has -pg cflag, because copy text to exec-mem will
# change the address.
# CFLAGS_mmap-exec := -pg

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

msync: msync.o
fexecve: fexecve.o
mmap-anon: mmap-anon.o
mmap-file: mmap-file.o
mremap-file: mremap-file.o
remap_file_pages: remap_file_pages.o
get_unmapped_page: get_unmapped_page.o mmap_helpers.o
mmap-multi-thread-copy: mmap-multi-thread-copy.o
mmap-exec: mmap-exec.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./mmap-multi-thread-copy /etc/os-release os-release 4

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o os-release

