SHELL = bash
include ../../../../tlbuild.mk



all:
	clang -g -c -O2 -target bpf -c program.c -o program.o

clean:
	rm -f program.o
