TARGETS :=
TARGETS += socketpair
TARGETS += getsockopt
TARGETS += setsockopt
TARGETS += gethostbyname
TARGETS += socket
TARGETS += bind
TARGETS += listen
TARGETS += accept
TARGETS += connect
TARGETS += shutdown
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

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
socketpair: socketpair.o
getsockopt: getsockopt.o
setsockopt: setsockopt.o
gethostbyname: gethostbyname.o
socket: socket.o
bind: bind.o
listen: listen.o
accept: accept.o
connect: connect.o
shutdown: shutdown.o
tcp-srv-1: tcp-srv-1.o
tcp-clt-1: tcp-clt-1.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(@)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
