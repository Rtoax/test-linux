SYS_IO_HEADER = /usr/include/sys/io.h

target-y :=
target-y += outb outw outl
target-y += inb inw inl
target-y += ioperm

# FIXME: Why rpi5 don't has sys/io.h
ifeq ($(wildcard $(SYS_IO_HEADER)),)
  target-y :=
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
