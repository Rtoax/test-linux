include ../../../tlbuild.mk
CLANG = clang

INCLUDE_PATH += -I/kernel-src/tools/lib/bpf

LIBRARY_PATH = -L/usr/local/lib64
BPFSO = -lbpf

.PHONY: clean 

clean:
	rm -f fetch.out save.out

fetch.out: 	map_pinning_fetch.c 
	clang -o fetch.out -lelf $(INCLUDE_PATH) $(LIBRARY_PATH) $(BPFSO) $?

save.out: 	map_pinning_save.c
	clang -o save.out -lelf $(INCLUDE_PATH) $(LIBRARY_PATH) $(BPFSO) $?

build: fetch.out save.out

.DEFAULT_GOAL := build
