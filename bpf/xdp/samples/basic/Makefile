# SPDX-License-Identifier: GPL-3.0
SHELL = bash

CLANG := clang

TARGETS :=
TARGETS += vmlinux.h
TARGETS += drop.o drop.g.o
TARGETS += proto.o

IF := lo

CFLAGS := -Wunknown-attributes


.PHONY: build
build: $(TARGETS)

%.o: %.c
	@echo -e "  CLANG  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CLANG) -O2 -Wall -target bpf -c $(<) -o $(@) ${CFLAGS}
	@llvm-objdump -S --no-show-raw-insn $(@)
	@llvm-objdump -S $(@)
	@$(CLANG) -O2 -Wall -target bpf -c $(<) -S -o $(<:.c=.S) ${CFLAGS}
	@llvm-mc -triple bpf -filetype=obj -o $(@) $(<:.c=.S) # LLVM 6.0
	@${CLANG} -O2 -Wall -target bpf -emit-llvm -c $(<) -o $(<:.c=.bc) ${CFLAGS}
	@llc $(<:.c=.bc) -march=bpf -filetype=obj -o $(@)
	@$(CLANG) -O2 -Wall -emit-llvm -S -c $(<) ${CFLAGS} -o -

%.g.o: %.c
	@echo -e "  CLANG-g  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@llc -march=bpf -mattr=help |& grep dwarfris
	@$(CLANG) -O2 -g -Wall -target bpf -emit-llvm -c $(<) -o $(<:.c=.g.bc) ${CFLAGS}
	@llc $(<:.c=.g.bc) -march=bpf -mattr=dwarfris -filetype=obj -o $(<:.c=.g.o)
	@$(CLANG) -target bpf -O2 -g -c -Xclang -target-feature -Xclang +dwarfris -c $(<) -o $(<:.c=.g.o) ${CFLAGS}
	@pahole $(<:.c=.g.o)
	@pahole -J $(<:.c=.g.o)
	@readelf -a $(<:.c=.g.o) | grep BTF

vmlinux.h:
	@echo -e "  BPFTOOL  \033[1m$(@)\033[m"
	@bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

attach:
	sudo ip link set dev ${IF} xdp obj drop.o

detach:
	sudo ip link set dev ${IF} xdp off

install:
	sudo bpftool prog load proto.o /sys/fs/bpf/proto
	sudo bpftool net attach xdp pinned /sys/fs/bpf/proto dev ${IF}
	sudo bpftool net show

uninstall:
	sudo bpftool net detach xdp dev ${IF}
	sudo rm -f /sys/fs/bpf/proto


clean:
	@rm -f ${TARGETS} *.o *.S *.bc
