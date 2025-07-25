sub-dir := poll
sub-dir += epoll
sub-dir += iovec
sub-dir += proxy
sub-dir += syscall
sub-dir += unix
sub-dir += tcp
sub-dir += sctp
sub-dir += udp
sub-dir += vsock
sub-dir += ipv6

targets := sockaddr-size
targets-liba := socket_helpers.a

include ../../template/main.mk

sockaddr-size: sockaddr-size.o
socket_helpers.a: socket_helpers.a.o
