target-y := aio_read
target-y += aio_write
target-y += aio_suspend
target-y += lio_listio

LDFLAGS := -lrt

include ../../template/main.mk

aio_read: aio_read.o
aio_write: aio_write.o
aio_suspend: aio_suspend.o
lio_listio: lio_listio.o
