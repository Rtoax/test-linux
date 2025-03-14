# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

include ../../../kconfig.mk

TARGETS := PR_CAPBSET_DROP
TARGETS += PR_GET_NAME
TARGETS += PR_SET_VMA_ANON_NAME
TARGETS += PR_GET_ENDIAN
TARGETS += PR_SET_SECCOMP

DEBUG := yes
CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

ifeq ($(CONFIG_ANON_VMA_NAME),y)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

PR_CAPBSET_DROP: PR_CAPBSET_DROP.o
PR_GET_NAME: PR_GET_NAME.o
PR_SET_VMA_ANON_NAME: PR_SET_VMA_ANON_NAME.o
PR_GET_ENDIAN: PR_GET_ENDIAN.o
PR_SET_SECCOMP: PR_SET_SECCOMP.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)


test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt
