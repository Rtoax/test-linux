SHELL = bash
include ../../../tlbuild.mk



CFLAGS := -Wall -Werror

all:
	# Compile bpf_program
	clang $(CFLAGS) -O2 -target bpf -c bpf_program.c -o bpf_program.o

	# Compile loader
	gcc $(CFLAGS) loader.c bpf_load.c -lelf trace_helpers.c -lbpf -o execsnoop

test:
	@echo "skip" >/dev/null

clean:
	rm -f *.out *.o execsnoop
