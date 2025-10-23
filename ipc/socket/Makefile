subdir-y := poll
subdir-y += epoll
subdir-y += iovec
subdir-y += proxy
subdir-y += syscall
subdir-y += unix
subdir-y += tcp
subdir-y += sctp
subdir-y += udp
subdir-y += vsock
subdir-y += ipv6

target-y := sockaddr-size

target-liba-y := socket_helpers.a
target-libso-y := libsocket_helpers.so

include ../../template/main.mk

socket_helpers.so.o: socket_helpers.h
libsocket_helpers.so: socket_helpers.so.o

sockaddr-size: sockaddr-size.o
socket_helpers.a: socket_helpers.a.o
