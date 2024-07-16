SHELL = bash


INTERFACE = eno1

all:
	@echo "Help:"
	@echo "=== test1-attach test1-detach"

test1-attach:
	clang -O2 -Wall -target bpf -c drop.c -o drop.o
	sudo ip link set dev ${INTERFACE} xdp obj drop.o
	llvm-objdump -S --no-show-raw-insn drop.o
	llvm-objdump -S drop.o

test1-detach:
	sudo ip link set dev ${INTERFACE} xdp off

show-asm1:
	clang -O2 -S -Wall -target bpf -c drop.c -o drop.S
	cat drop.S
	llvm-mc -triple bpf -filetype=obj -o drop.o drop.S # LLVM 6.0

show-asm2:
	clang -O2 -Wall -target bpf -emit-llvm -c drop.c -o drop.bc
	llc drop.bc -march=bpf -filetype=obj -o drop.o
	clang -O2 -Wall -emit-llvm -S -c drop.c -o -

dwarf:
	llc -march=bpf -mattr=help |& grep dwarfris
	clang -O2 -g -Wall -target bpf -emit-llvm -c drop.c -o drop.bc
	llc drop.bc -march=bpf -mattr=dwarfris -filetype=obj -o drop.o
	clang -target bpf -O2 -g -c -Xclang -target-feature -Xclang +dwarfris -c drop.c -o drop.o
	pahole drop.o

dwarf2:
	clang -target bpf -O2 -Wall -g -c -Xclang -target-feature -Xclang +dwarfris -c drop.c -o drop.o
	pahole -J drop.o
	readelf -a drop.o | grep BTF

clean:
	rm -f *.o *.S *.bc
