SHELL = bash
include ../../../tlbuild.mk

LIBAIO_HDR = /usr/include/libaio.h

TARGETS :=
TARGETS += libaio
TARGETS += epoll

ifeq ($(wildcard $(LIBAIO_HDR)),)
  $(error "ERROR: Must install libaio development header")
endif

CC = gcc

LDFLAGS :=
CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

ifneq ($(wildcard $(LIBAIO_HDR)),)
  CFLAGS += -laio
  LDFLAGS += -laio
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

libaio: libaio.o helpers.o
epoll: epoll.o

PFX_CC := CC
ifeq ($(CC),clang)
  PFX_CC := CLANG
endif

%.o: %.c
	@echo -e "  ${PFX_CC}  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(LDFLAGS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.txt *.dat
