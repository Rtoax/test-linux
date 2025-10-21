target-y :=
target-y += socketpair
target-y += getsockopt
target-y += setsockopt
target-y += getsockname
target-y += socket
target-y += bind bind-ENOTSOCK
target-y += listen
target-y += accept
target-y += connect
target-y += shutdown
target-y += recv
target-y += tcp-srv-1 tcp-clt-1
target-y += AF_XDP

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
