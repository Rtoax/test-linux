SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


KERN_CONFIG=/boot/config-$(shell uname -r)

ifneq ($(wildcard $(KERN_CONFIG)),)
include ${KERN_CONFIG}
else
$(warning "WARNING: not found ${KERN_CONFIG}")
endif

TARGETS :=
TARGETS += msync
TARGETS += fexecve
TARGETS += mmap-anon
TARGETS += mmap-file
TARGETS += remap_file_pages
TARGETS += get_unmapped_page
TARGETS += mmap-multi-thread-copy
TARGETS += mmap-exec

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -lrt

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
msync: msync.o
fexecve: fexecve.o
mmap-anon: mmap-anon.o
mmap-file: mmap-file.o
remap_file_pages: remap_file_pages.o
get_unmapped_page: get_unmapped_page.o helpers.o
mmap-multi-thread-copy: mmap-multi-thread-copy.o
mmap-exec: mmap-exec.o

ifeq ($(CONFIG_ANON_VMA_NAME),y)
  CFLAGS_mmap-anon := -DCONFIG_ANON_VMA_NAME=1
endif
# mmap-exec never should has -pg cflag, because copy text to exec-mem will
# change the address.
# CFLAGS_mmap-exec := -pg

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./mmap-multi-thread-copy /etc/os-release os-release 4

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o os-release

