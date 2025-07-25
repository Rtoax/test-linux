targets := aio_read
targets += aio_write
targets += aio_suspend
targets += lio_listio

CFLAGS :=
CFLAGS += -lrt

include ../../template/main.mk

aio_read: aio_read.o
aio_write: aio_write.o
aio_suspend: aio_suspend.o
lio_listio: lio_listio.o
