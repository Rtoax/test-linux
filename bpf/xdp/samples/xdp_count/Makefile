SHELL = bash
include ../../../../tlbuild.mk


# ref: https://www.containiq.com/post/btf-bpf-type-format
#

all:
	clang -O2 -Wall -g -target bpf -c xdp_count.c -o xdp_count.o
	sudo bpftool prog load xdp_count.o /sys/fs/bpf/xdp_count type xdp
	sudo bpftool prog list

clean:
	rm -f *.o
