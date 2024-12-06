SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



all:
	clang -g -c -O2 -target bpf -c program.c -o program.o

clean:
	rm -f program.o
