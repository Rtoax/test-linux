
IFNAME=enp1s0

all:
	clang -g -c -O2 -target bpf -c program.c -o program.o

load:
	sudo ip link set dev ${IFNAME} xdp obj program.o sec mysection

unload:
	sudo ip link set dev ${IFNAME} xdp off

clean:
	rm -f program.o
