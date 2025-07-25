targets := capget
targets += version

ifeq ($(wildcard /usr/include/sys/capability.h),)
  $(error "ERROR: not found capability development")
endif

include ../../../template/main.mk

capget: capget.o
version: version.o
