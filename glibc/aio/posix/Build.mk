target-y := aio_read
target-y += aio_write
target-y += aio_suspend
target-y += lio_listio

LDFLAGS := -lrt
