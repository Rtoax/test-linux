target-y := write write-EBADF

CFLAGS := -pthread
CFLAGS_write := -Wno-error=unused-variable
