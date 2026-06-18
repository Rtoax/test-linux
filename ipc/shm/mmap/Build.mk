target-y += shm-reader shm-writer
target-y += mmap-reader mmap-writer

post-y += post0

CFLAGS := -g -ggdb -O0
LDFLAGS += -lrt
