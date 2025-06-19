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

include ../../../template/main.mk

outb: outb.o
outw: outw.o
outl: outl.o
inb: inb.o
inw: inw.o
inl: inl.o
ioperm: ioperm.o
