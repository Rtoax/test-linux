target-y := crc32b
target-y += crc32w

CFLAGS += -g -ggdb
CFLAGS += -O3
CFLAGS += -march=armv8.1-a
LDFLAGS += -pthread
