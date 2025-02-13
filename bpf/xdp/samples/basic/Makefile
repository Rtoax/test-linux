# SPDX-License-Identifier: GPL-3.0
include ../../../../tlbuild.mk

CC := gcc
CLANG := clang

TARGETS_KERN :=
TARGETS_USER :=

TARGETS_KERN += vmlinux.h
TARGETS_KERN += drop.o
TARGETS_KERN += proto.o
TARGETS_KERN += config_map.kern.o

ifdef DEBUG
  TARGETS_KERN += drop.g.o
  TARGETS_KERN += proto.g.o
endif

IF := lo

CFLAGS_KERN := -Wno-unknown-attributes
CFLAGS_KERN += -Wno-compare-distinct-pointer-types

CFLAGS_USER := -lbpf
LDFLAGS_USER := -lbpf

.PHONY: build
build: $(TARGETS_KERN) ${TARGETS_USER}

%.o: %.c
	@echo -e "  CLANG-K  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -O2 -Wall -target bpf -c $(<) -o $(@) ${CFLAGS_KERN}
	${Q}llvm-objdump -S --no-show-raw-insn $(@)
	${Q}llvm-objdump -S $(@)
	${Q}$(CLANG) -O2 -Wall -target bpf -c $(<) -S -o $(<:.c=.S) ${CFLAGS_KERN}
	${Q}llvm-mc -triple bpf -filetype=obj -o $(@) $(<:.c=.S) # LLVM 6.0
	${Q}$(CLANG) -O2 -Wall -target bpf -emit-llvm -c $(<) -o $(<:.c=.bc) ${CFLAGS_KERN}
	${Q}llc $(<:.c=.bc) -march=bpf -filetype=obj -o $(@)
	${Q}$(CLANG) -O2 -Wall -emit-llvm -S -c $(<) ${CFLAGS_KERN} -o -

%.g.o: %.c
	@echo -e "  CLANG-g  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}llc -march=bpf -mattr=help |& grep dwarfris
	${Q}$(CLANG) -O2 -g -Wall -target bpf -emit-llvm -c $(<) -o $(<:.c=.g.bc) ${CFLAGS_KERN}
	${Q}llc $(<:.c=.g.bc) -march=bpf -mattr=dwarfris -filetype=obj -o $(<:.c=.g.o)
	${Q}$(CLANG) -target bpf -O2 -g -c -Xclang -target-feature -Xclang +dwarfris -c $(<) -o $(<:.c=.g.o) ${CFLAGS_KERN}
	${Q}pahole $(<:.c=.g.o)
	${Q}pahole -J $(<:.c=.g.o)
	${Q}readelf -a $(<:.c=.g.o) | grep BTF

%.uo: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS_USER) $(CFLAGS_USER_$(*))

$(TARGETS_USER): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS_USER) $(LDFLAGS_USER_$(*))

vmlinux.h:
	@echo -e "  BPFTOOL  \033[1m$(@)\033[m"
	${Q}bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

attach:
	${Q}sudo ip link set dev ${IF} xdp obj drop.o

detach:
	${Q}sudo ip link set dev ${IF} xdp off

install:
	${Q}sudo bpftool prog load proto.o /sys/fs/bpf/proto
	${Q}sudo bpftool net attach xdp pinned /sys/fs/bpf/proto dev ${IF}
	${Q}sudo bpftool net show

uninstall:
	${Q}sudo bpftool net detach xdp dev ${IF}
	${Q}sudo rm -f /sys/fs/bpf/proto

clean:
	${Q}rm -f ${TARGETS_KERN} ${TARGETS_USER} *.o *.S *.bc *.uo
