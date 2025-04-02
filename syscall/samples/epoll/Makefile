include ../../../tlbuild.mk
include ../../../kernel.mk

TARGETS := eventfd
TARGETS += eventfd-epoll_pwait
# kernel commit 58169a52ebc9 ("epoll: add syscall epoll_pwait2")
# v5.10-11840-g58169a52ebc9
ifeq ($(call kernel_newer_than,5,10,0),y)
  $(info Kernel support epoll_pwait2)
  TARGETS += eventfd-epoll_pwait2
endif
TARGETS += level-triggered edge-triggered
TARGETS += tcp-echo

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
# CFLAGS += -DUSE_ONESHOT=1
CFLAGS += -pthread

LDFLAGS := -pthread

ifdef SYSCALL
  CFLAGS += -DSYSCALL=1
endif

CFLAGS_eventfd-epoll_pwait := -DEPOLL_PWAIT=1
CFLAGS_eventfd-epoll_pwait2 := -DEPOLL_PWAIT2=1

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

epoll_helpers.o: epoll_helpers.h

eventfd: eventfd.o epoll_helpers.o
eventfd-epoll_pwait: eventfd-epoll_pwait.o epoll_helpers.o
eventfd-epoll_pwait2: eventfd-epoll_pwait2.o epoll_helpers.o
level-triggered: level-triggered.o
edge-triggered: edge-triggered.o
tcp-echo: tcp-echo.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt
