TARGETS := aio_read
TARGETS += aio_write
TARGETS += aio_suspend
TARGETS += lio_listio

CFLAGS :=
CFLAGS += -lrt

include ../../template/main.mk

aio_read: aio_read.o
aio_write: aio_write.o
aio_suspend: aio_suspend.o
lio_listio: lio_listio.o
