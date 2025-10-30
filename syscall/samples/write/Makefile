target-y := write write-EBADF

CFLAGS := -pthread
CFLAGS_write := -Wno-error=unused-variable

include ../../../template/main.mk

write: write.o
write-EBADF: write-EBADF.o
