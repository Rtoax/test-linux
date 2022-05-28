
all:
	# Compile bpf_program
	clang -O2 -target bpf -c bpf_program.c -o bpf_program.o

	# Compile loader
	gcc loader.c bpf_load.c -lelf trace_helpers.c -lbpf -o execsnoop.out

clean:
	rm -f *.out *.o
