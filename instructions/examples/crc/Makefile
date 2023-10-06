TARGETS := crc32b
TARGETS += crc32w

# User
ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

user: $(TARGETS)

kernel:
	make -C ${KERNELDIR} M=$(PWD) modules

crc32b: crc32b.o
crc32w: crc32w.o

CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -O3
CFLAGS += -pthread

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	rm -f *.o ${TARGETS}
