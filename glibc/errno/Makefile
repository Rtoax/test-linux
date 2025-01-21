SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include ../glibc.mk

TARGETS := nr_errno
TARGETS += __errno_location
TARGETS += EDOM
TARGETS += ENOENT

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

DEBUG = yes
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread

CFLAGS += -DLIBC___ERRNO_LOCATION_SYMADDR=${LIBC___ERRNO_LOCATION_SYMADDR}

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
endif

.PHONY: build
build: nr_errno.h ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

nr_errno.h:
	$(shell bash errno.sh)

nr_errno: nr_errno.o
__errno_location: __errno_location.o
EDOM: EDOM.o
ENOENT: ENOENT.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.out nr_errno.h
