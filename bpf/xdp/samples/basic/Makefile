# SPDX-License-Identifier: GPL-3.0
include verbose.mk
include bpf/xdp.mk

CC := gcc
CLANG := clang

targets-kern += vmlinux.h
targets-kern += proto.o

ifdef DEBUG
  targets-kern += proto.g.o
endif

CFLAGS_KERN := -Wno-unknown-attributes
CFLAGS_KERN += -Wno-compare-distinct-pointer-types

CFLAGS_USER := -lbpf
LDFLAGS_USER := -lbpf

.PHONY: build
build: $(targets-kern) ${targets-user}

%.o: %.c
	@echo -e "  CLANG-K  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -O2 -target bpf -c $(<) -o $(@) ${CFLAGS_KERN}

%.g.o: %.c
	@echo -e "  CLANG-g  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -O2 -g -target bpf -emit-llvm -c $(<) -o $(<:.c=.g.bc) ${CFLAGS_KERN}
	${Q}llc $(<:.c=.g.bc) -march=bpf -mattr=dwarfris -filetype=obj -o $(<:.c=.g.o)
	${Q}pahole $(<:.c=.g.o)
	${Q}pahole -J $(<:.c=.g.o)
	${Q}readelf -a $(<:.c=.g.o) | grep BTF

%.uo: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS_USER) $(CFLAGS_USER_$(*))

$(targets-user): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS_USER) $(LDFLAGS_USER_$(*))

vmlinux.h:
	$(Q)bpftool btf dump file /sys/kernel/btf/vmlinux format c > ${@}

install:
	$(call attach_xdp,lo,proto.o,proto)

uninstall:
	$(call detach_xdp,lo,proto)

clean:
	${Q}rm -f ${targets-kern} ${targets-user} *.o *.S *.bc *.uo
