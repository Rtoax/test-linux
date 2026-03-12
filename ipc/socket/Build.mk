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

target-liba-y := libsocket_helpers.a
target-libso-y := libsocket_helpers.so

libsocket_helpers.a-objs := socket_helpers.a.o
libsocket_helpers.so-objs := socket_helpers.so.o
