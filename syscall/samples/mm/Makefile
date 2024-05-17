TARGETS :=
TARGETS += brk sbrk sbrk-bss
TARGETS += membarrier
TARGETS += mlock mlockall
TARGETS += pkey_alloc
TARGETS += pkey_free
TARGETS += pkey_mprotect
TARGETS += mprotect
TARGETS += mbind

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"
	make -C mmap
	make -C madvise
	make -C memfd_create

# Add more object.o file
brk: brk.o
sbrk: sbrk.o
sbrk-bss: sbrk-bss.o
membarrier: membarrier.o
mlock: mlock.o
mlockall: mlockall.o
pkey_alloc: pkey_alloc.o
pkey_free: pkey_free.o
pkey_mprotect: pkey_mprotect.o
mprotect: mprotect.o
mbind: mbind.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
	make -C mmap clean
	make -C madvise clean
	make -C memfd_create clean
