include ../../../template/kernel.mk

targets := eventfd
targets += eventfd-epoll_pwait
# kernel commit 58169a52ebc9 ("epoll: add syscall epoll_pwait2")
# v5.10-11840-g58169a52ebc9
ifeq ($(call kver_gt,5,10,0),y)
  $(info Kernel support epoll_pwait2)
  targets += eventfd-epoll_pwait2
endif
targets += level-triggered edge-triggered
targets += tcp-echo

CFLAGS += -pthread
LDFLAGS := -pthread

ifdef SYSCALL
  CFLAGS += -DSYSCALL=1
endif

CFLAGS_eventfd-epoll_pwait := -DEPOLL_PWAIT=1
CFLAGS_eventfd-epoll_pwait2 := -DEPOLL_PWAIT2=1

include ../../../template/main.mk

epoll_helpers.o: epoll_helpers.h

eventfd: eventfd.o epoll_helpers.o
eventfd-epoll_pwait: eventfd-epoll_pwait.o epoll_helpers.o
eventfd-epoll_pwait2: eventfd-epoll_pwait2.o epoll_helpers.o
level-triggered: level-triggered.o
edge-triggered: edge-triggered.o
tcp-echo: tcp-echo.o
