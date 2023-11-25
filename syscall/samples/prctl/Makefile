include /boot/config-$(shell uname -r)

TARGETS := PR_CAPBSET_DROP
TARGETS += PR_GET_NAME
TARGETS += PR_SET_VMA_ANON_NAME

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

ifeq ($(CONFIG_ANON_VMA_NAME),y)
CFLAGS_PR_SET_VMA_ANON_NAME := -DCONFIG_ANON_VMA_NAME=1
endif

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)


test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
