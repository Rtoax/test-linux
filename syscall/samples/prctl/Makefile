KERN_CONFIG=/boot/config-$(shell uname -r)

ifneq ($(wildcard $(KERN_CONFIG)),)
include ${KERN_CONFIG}
else
$(warning "WARNING: not found ${KERN_CONFIG}")
endif

SHELL = /bin/bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS := PR_CAPBSET_DROP
TARGETS += PR_GET_NAME
TARGETS += PR_SET_VMA_ANON_NAME
TARGETS += PR_GET_ENDIAN
TARGETS += PR_SET_SECCOMP

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
PR_CAPBSET_DROP: PR_CAPBSET_DROP.o
PR_GET_NAME: PR_GET_NAME.o
PR_SET_VMA_ANON_NAME: PR_SET_VMA_ANON_NAME.o
PR_GET_ENDIAN: PR_GET_ENDIAN.o
PR_SET_SECCOMP: PR_SET_SECCOMP.o

ifeq ($(CONFIG_ANON_VMA_NAME),y)
CFLAGS_PR_SET_VMA_ANON_NAME := -DCONFIG_ANON_VMA_NAME=1
endif

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)


test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt
