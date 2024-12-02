# SPDX-License-Identifier: GPL-3.0
SHELL = bash

CLANG := clang

TARGETS :=
TARGETS += drop.o drop.g.o

IF := eno1

.PHONY: build
build: $(TARGETS)

%.o: %.c
	@echo -e "  CLANG  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CLANG) -O2 -Wall -target bpf -c $(<) -o $(@)
	@llvm-objdump -S --no-show-raw-insn $(@)
	@llvm-objdump -S $(@)
	@$(CLANG) -O2 -Wall -target bpf -c $(<) -S -o $(<:.c=.S)
	@llvm-mc -triple bpf -filetype=obj -o $(@) $(<:.c=.S) # LLVM 6.0
	@${CLANG} -O2 -Wall -target bpf -emit-llvm -c $(<) -o $(<:.c=.bc)
	@llc $(<:.c=.bc) -march=bpf -filetype=obj -o $(@)
	@$(CLANG) -O2 -Wall -emit-llvm -S -c $(<) -o -

%.g.o: %.c
	@llc -march=bpf -mattr=help |& grep dwarfris
	@$(CLANG) -O2 -g -Wall -target bpf -emit-llvm -c $(<) -o $(<:.c=.g.bc)
	@llc $(<:.c=.g.bc) -march=bpf -mattr=dwarfris -filetype=obj -o $(<:.c=.g.o)
	@$(CLANG) -target bpf -O2 -g -c -Xclang -target-feature -Xclang +dwarfris -c $(<) -o $(<:.c=.g.o)
	@pahole $(<:.c=.g.o)
	@pahole -J $(<:.c=.g.o)
	@readelf -a $(<:.c=.g.o) | grep BTF

attach:
	@echo sudo ip link set dev ${IF} xdp obj drop.o

detach:
	@echo sudo ip link set dev ${IF} xdp off

clean:
	@rm -f ${TARGETS} *.o *.S *.bc
