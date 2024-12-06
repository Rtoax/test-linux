SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += socketpair
TARGETS += getsockopt
TARGETS += setsockopt
TARGETS += getsockname
TARGETS += socket
TARGETS += bind bind-ENOTSOCK
TARGETS += listen
TARGETS += accept
TARGETS += connect
TARGETS += shutdown
TARGETS += recv
TARGETS += tcp-srv-1 tcp-clt-1

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
# TODO: Remove openat2 from TARGETS
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -I../../../libs/

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
socketpair: socketpair.o
getsockopt: getsockopt.o
setsockopt: setsockopt.o
getsockname: getsockname.o
socket: socket.o
bind: bind.o
bind-ENOTSOCK: bind-ENOTSOCK.o
listen: listen.o
accept: accept.o
connect: connect.o fd.o
shutdown: shutdown.o
recv: recv.o
tcp-srv-1: tcp-srv-1.o
tcp-clt-1: tcp-clt-1.o

fd.c:
	@echo -e "  COPY  \033[1m$(@)\033[m"
	@cp ../../../libs/fd.c fd.c

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt fd.c
