target-y += shm-reader shm-writer
target-y += mmap-reader mmap-writer

target-post-y += post0

CFLAGS := -g -ggdb -O0
LDFLAGS += -lrt

include main.mk

post0:
	$(call log_tgt,TEST,$(@))
	$(Q)./shm-writer && ./shm-reader
	$(Q)./mmap-writer && ./mmap-reader
