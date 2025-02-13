# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk


TARGETS :=
TARGETS += setxattr
TARGETS += getxattr
TARGETS += listxattr
TARGETS += demo-1

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS}
	@touch a.txt
	@echo -e " \033[1;33m Done \033[m"

setxattr: setxattr.o
getxattr: getxattr.o
listxattr: listxattr.o
demo-1: demo-1.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.txt
