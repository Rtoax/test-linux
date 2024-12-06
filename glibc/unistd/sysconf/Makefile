SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



TARGETS := NPROCESSORS
TARGETS += PAGESIZE
TARGETS += sysconf

OS := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | sed 's/"//g')

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif
ifdef STATIC
CFLAGS += -static
$(info Defined STATIC)
endif

.PHONY: build
build: confs_def.h ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

confs_def.h: sysconf.sh
	$(shell bash sysconf.sh)

# Add more object.o file
NPROCESSORS: NPROCESSORS.o
PAGESIZE: PAGESIZE.o
sysconf: sysconf.o

CFLAGS_NPROCESSORS := -D_NPROCESSORS=1
LDFLAGS_NPROCESSORS :=
CFLAGS_sysconf := -Wno-error

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o gen-sysconf-* confs_def.h
