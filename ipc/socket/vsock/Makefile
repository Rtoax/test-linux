include kconfig.mk

subdir-y := samples

target-y :=
target-y += vsock

include main.mk

vsock_helpers.o: vsock_helpers.h
vsock: vsock.o vsock_helpers.o
