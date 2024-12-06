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
TARGETS += shmctl
TARGETS += reader
TARGETS += writer writer-hugetlb
TARGETS += private

CFLAGS := -g -ggdb -O0

ALL: $(TARGETS)

shmctl: shmctl.o
reader: reader.o
writer: writer.o
writer-hugetlb: writer-hugetlb.o
private: private.o

CFLAGS_writer-hugetlb := -DHAVE_HUGETLB=1

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: $(TARGETS)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./writer && ./reader
	./private

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
