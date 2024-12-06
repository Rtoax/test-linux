SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


# ref: https://www.containiq.com/post/btf-bpf-type-format
#

all:
	clang -O2 -Wall -g -target bpf -c xdp_count.c -o xdp_count.o
	sudo bpftool prog load xdp_count.o /sys/fs/bpf/xdp_count type xdp
	sudo bpftool prog list

clean:
	rm -f *.o
