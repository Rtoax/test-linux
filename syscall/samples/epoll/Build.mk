include kernel.mk

target-y := eventfd
target-y += eventfd-epoll_pwait
# kernel commit 58169a52ebc9 ("epoll: add syscall epoll_pwait2")
# v5.10-11840-g58169a52ebc9
ifeq ($(call kver_gt,5,10,0),y)
  $(info Kernel support epoll_pwait2)
  target-y += eventfd-epoll_pwait2
endif
target-y += level-triggered edge-triggered
target-y += tcp-echo

eventfd-objs := ${OUTPUT}epoll_helpers.o
eventfd-epoll_pwait-objs := ${OUTPUT}epoll_helpers.o
eventfd-epoll_pwait2-objs := ${OUTPUT}epoll_helpers.o

LDFLAGS := -pthread

ifdef SYSCALL
  CFLAGS += -DSYSCALL=1
endif

CFLAGS_eventfd-epoll_pwait := -DEPOLL_PWAIT=1
CFLAGS_eventfd-epoll_pwait2 := -DEPOLL_PWAIT2=1
