SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


CC := gcc

TARGETS :=
TARGETS += shm-reader shm-writer
TARGETS += mmap-reader mmap-writer

CFLAGS := -g -ggdb -O0
CFLAGS += -lrt

ALL: $(TARGETS)

shm-reader: shm-reader.o
shm-writer: shm-writer.o
mmap-reader: mmap-reader.o
mmap-writer: mmap-writer.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: $(TARGETS)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./shm-writer && ./shm-reader
	./mmap-writer && ./mmap-reader

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
