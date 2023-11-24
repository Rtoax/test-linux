
TARGETS += brk sbrk sbrk-bss
TARGETS += memfd_create memfd_create-dup2
TARGETS += membarrier
TARGETS += mlock mlockall
TARGETS += pkey_alloc
TARGETS += pkey_free
TARGETS += pkey_mprotect

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
	make -C mmap
	make -C madvise

# Add more object.o file
brk: brk.o
sbrk: sbrk.o
sbrk-bss: sbrk-bss.o
memfd_create: memfd_create.o
memfd_create-dup2: memfd_create-dup2.o
membarrier: membarrier.o
mlock: mlock.o
mlockall: mlockall.o
pkey_alloc: pkey_alloc.o
pkey_free: pkey_free.o
pkey_mprotect: pkey_mprotect.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
	make -C mmap clean
	make -C madvise clean

