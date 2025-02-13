include ../../../tlbuild.mk


all:
	clang -O2 -target bpf -c bpf_program.c -o bpf_program.o
	clang -o loader -I.  bpf_load.c loader.c -lbpf -lelf

clean:
	rm -f *.o loader
