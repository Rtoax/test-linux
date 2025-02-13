include ../../tlbuild.mk


TARGETS := aio_read
TARGETS += aio_write
TARGETS += aio_suspend
TARGETS += lio_listio

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lrt

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"
	@echo -e "  SRCTREE  ${ABS_SRCTREE}"

# Add more object.o file
aio_read: aio_read.o
aio_write: aio_write.o
aio_suspend: aio_suspend.o
lio_listio: lio_listio.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt *.dat
