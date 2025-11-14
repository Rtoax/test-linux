target-y :=
target-y += consumer producer

CFLAGS :=
CFLAGS += -I. -ggdb

include main.mk

consumer: consumer.o mlinklist.o
producer: producer.o mlinklist.o
