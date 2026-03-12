target-y += libaio
target-y += epoll

libaio-objs := aio_helpers.o

LDFLAGS += -laio
