include /boot/config-$(shell uname -r)

TARGETS += fexecve
TARGETS += mmap-anon
TARGETS += mmap-file
TARGETS += remap_file_pages

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

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
fexecve: fexecve.o
mmap-anon: mmap-anon.o
mmap-file: mmap-file.o
remap_file_pages: remap_file_pages.o

ifeq ($(CONFIG_ANON_VMA_NAME),y)
CFLAGS_mmap-anon := -DCONFIG_ANON_VMA_NAME=1
endif

%.o: %.c
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "LD   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o os-release

