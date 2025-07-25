SYS_IO_HEADER = /usr/include/sys/io.h

targets :=
targets += outb outw outl
targets += inb inw inl
targets += ioperm

# FIXME: Why rpi5 don't has sys/io.h
ifeq ($(wildcard $(SYS_IO_HEADER)),)
  targets :=
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
