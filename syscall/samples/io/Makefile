include ../../../tlbuild.mk

CC := gcc

SYS_IO_HEADER = /usr/include/sys/io.h

TARGETS :=
TARGETS += outb outw outl
TARGETS += inb inw inl
TARGETS += ioperm

# FIXME: Why rpi5 don't has sys/io.h
ifeq ($(wildcard $(SYS_IO_HEADER)),)
  TARGETS :=
  $(warning "WARNING: Not found ${SYS_IO_HEADER}")
  $(warning "WARNING: Maybe you need to install glibc-headers")
endif


CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -Wall -Wpedantic -O

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

outb: outb.o
outw: outw.o
outl: outl.o
inb: inb.o
inw: inw.o
inl: inl.o
ioperm: ioperm.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
