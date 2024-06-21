Asynchronous I/O
================

# Syscalls

```c
#include <linux/aio_abi.h>
#include <libaio.h>
```

- `io_setup(2)`
- `io_destroy(2)`
- `io_submit(2)`
- `io_cancel(2)`
- `io_getevents(2)`
- `io_pgetevents(2)`


## Libaio


# Posix AIO

> man aio(7)

```c
#include <aio.h>
```

- `aio_read(3)`
- `aio_write(3)`
- `aio_fsync(3)`
- `aio_error(3)`
- `aio_return(3)`
- `aio_suspend(3)`
- `aio_cancel(3)`
- `lio_listio(3)`


# Sysfs

- `/sys/block/$BLK/device/queue_count`
- `/sys/block/$BLK/queue/nr_requests`
- `/sys/block/$BLK/queue/max_sectors_kb`


# Procfs

- `/proc/sys/fs/aio-nr`
- `/proc/sys/fs/aio-max-nr`


# Links

- https://github.com/littledan/linux-aio
