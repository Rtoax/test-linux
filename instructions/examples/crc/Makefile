SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS := crc32b
TARGETS += crc32w

# User
ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

user: $(TARGETS)

kernel:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

crc32b: crc32b.o
crc32w: crc32w.o

CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -O3
CFLAGS += -pthread
CFLAGS += -march=armv8.1-a

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	rm -f *.o ${TARGETS}
