Asynchronous I/O
================

# Syscalls

- `io_setup`
- `io_destroy`
- `io_submit`
- `io_cancel`
- `io_getevents`
- `io_pgetevents`


# Posix AIO

> man aio(7)

- `aio_read`
- `aio_write`
- `aio_fsync`
- `aio_error`
- `aio_return`
- `aio_suspend`
- `aio_cancel`
- `lio_listio`


# Libaio


# Sysfs

- `/sys/block/$BLK/device/queue_count`
- `/sys/block/$BLK/queue/nr_requests`
- `/sys/block/$BLK/queue/max_sectors_kb`


# Procfs

- `/proc/sys/fs/aio-nr`
- `/proc/sys/fs/aio-max-nr`


# Links

- https://github.com/littledan/linux-aio
