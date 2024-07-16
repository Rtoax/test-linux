SHELL = bash

TARGETS :=
TARGETS += htonl
TARGETS += htons
TARGETS += ntohl
TARGETS += ntohs
TARGETS += inet_ntoa
TARGETS += inet_ntop
TARGETS += inet_pton
TARGETS += inet_aton
TARGETS += inet_addr
TARGETS += inet_network

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

htonl: htonl.o
htons: htons.o
ntohl: ntohl.o
ntohs: ntohs.o
inet_ntoa: inet_ntoa.o
inet_pton: inet_pton.o
inet_ntop: inet_ntop.o
inet_aton: inet_aton.o
inet_addr: inet_addr.o
inet_network: inet_network.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.out
