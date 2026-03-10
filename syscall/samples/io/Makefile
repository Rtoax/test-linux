SYS_IO_HEADER = /usr/include/sys/io.h

target-y += outb outw outl
target-y += inb inw inl
target-y += ioperm

# FIXME: Why rpi5 don't has sys/io.h
ifeq ($(wildcard $(SYS_IO_HEADER)),)
  target-y :=
  $(warning "WARNING: Not found ${SYS_IO_HEADER}")
  $(warning "WARNING: Maybe you need to install glibc-headers")
endif

include main.mk
