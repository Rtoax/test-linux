include bpf/libbpf.mk

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
target-${HAVE_LIBBPF} += AF_XDP

connect-objs := fd.o

include main.mk
