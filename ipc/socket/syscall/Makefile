include ../../../tlbuild.mk


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
TARGETS += AF_XDP

DEBUG := yes
CC := gcc

CFLAGS :=
CFLAGS += -I../../
CFLAGS += -I../../../libs/

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

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
AF_XDP: AF_XDP.o

fd.c:
	@echo -e "  COPY  \033[1m$(@)\033[m"
	${Q}cp ../../../libs/fd.c fd.c

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt fd.c
