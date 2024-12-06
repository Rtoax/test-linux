SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


# ref: https://www.kernel.org/doc/html/latest/bpf/btf.html
# 6. BTF Generation

all: t1 t2 t2.s

t1:
	gcc -c -O2 -g t.c
	pahole -JV t.o

t2:
	clang -c -g -O2 -target bpf t2.c
	readelf -S t2.o

t2.s:
	clang -S -g -O2 -target bpf t2.c
	cat t2.s

clean:
	rm -f *.o *.s *.S

