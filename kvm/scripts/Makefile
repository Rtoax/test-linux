# Just support x86_64 right now
ifeq ($(shell uname -m),x86_64)
  targets := ioctl_values
endif

include ../../template/main.mk

ioctl_values: ioctl_values.o
