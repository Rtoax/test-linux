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

include ../../template/main.mk

sockaddr-size: sockaddr-size.o
socket_helpers.a: socket_helpers.a.o
