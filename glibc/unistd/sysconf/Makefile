include ../../../tlbuild.mk

TARGETS := NPROCESSORS
TARGETS += PAGESIZE
TARGETS += sysconf

OS := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | sed 's/"//g')

DEBUG := yes
CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

ifdef STATIC
  CFLAGS += -static
  MAKEFLAGS += STATIC=1
  $(info Defined STATIC)
endif

.PHONY: build
build: confs_def.h ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

confs_def.h: sysconf.sh
	$(shell bash sysconf.sh)

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
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o gen-sysconf-* confs_def.h
