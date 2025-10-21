target-y := mq_open
target-y += mq_getattr
target-y += mq_notify
target-y += multi-thread-minimal multi-thread

CFLAGS :=
CFLAGS += -lrt

CFLAGS_multi-thread := -pthread

include ../../../../template/main.mk

mq_open: mq_open.o
mq_getattr: mq_getattr.o
mq_notify: mq_notify.o
multi-thread-minimal: multi-thread-minimal.o
multi-thread: multi-thread.o
