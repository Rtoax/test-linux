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

include ../../../template/main.mk

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
