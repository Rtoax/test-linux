build: vmlinux.h
	clang -g -c -O2 -target bpf -c program.c -o program.o

vmlinux.h:
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > ${@}

clean:
	rm -f program.o
