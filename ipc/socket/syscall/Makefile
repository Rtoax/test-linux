targets :=
targets += socketpair
targets += getsockopt
targets += setsockopt
targets += getsockname
targets += socket
targets += bind bind-ENOTSOCK
targets += listen
targets += accept
targets += connect
targets += shutdown
targets += recv
targets += tcp-srv-1 tcp-clt-1
targets += AF_XDP

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
