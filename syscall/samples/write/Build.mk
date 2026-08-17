target-y := write write-EBADF

CFLAGS_write := -Wno-error=unused-variable
LDFLAGS := -pthread
