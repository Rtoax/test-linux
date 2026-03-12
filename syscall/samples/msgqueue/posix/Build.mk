target-y := mq_open
target-y += mq_getattr
target-y += mq_notify
target-y += multi-thread-minimal multi-thread

CFLAGS += -lrt
CFLAGS_multi-thread := -pthread
