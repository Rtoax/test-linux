target-y += shm-reader shm-writer
target-y += mmap-reader mmap-writer

CFLAGS := -g -ggdb -O0
LDFLAGS += -lrt

target-test-y += test0

include main.mk

test0:
	$(call log_tgt,TEST,$(@))
	$(Q)./shm-writer && ./shm-reader
	$(Q)./mmap-writer && ./mmap-reader
