include ../../../../../tlbuild.mk


# -*- Makefile -*-
ccflags-y := -I$(src)/../include
MODULES_DIR := /lib/modules/$(shell uname -r)
KERNEL_DIR := ${MODULES_DIR}/build

obj-m += xt_ipaddr.o

all:
	${Q}make -C ${KERNEL_DIR} M=$$PWD;
modules:
	${Q}make -C ${KERNEL_DIR} M=$$PWD $@;
modules_install:
	${Q}make -C ${KERNEL_DIR} M=$$PWD $@;
clean:
	${Q}make -C ${KERNEL_DIR} M=$$PWD $@;