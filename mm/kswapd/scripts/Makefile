SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



all:
	gcc mmap.c -o mmap.out -D_GNU_SOURCE
clean:
	rm -f mmap.out
