# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


IF := lo
$(warning "Specify IF=[Interface] like IF=lo")

.PHONY: all
all: $(BPF_OBJ)
	@clang -g -c -O2 -target bpf -c program.c -o program.o
	@echo >&2 ""
	@echo >&2 " make"
	@echo >&2 " make   load [IF=enp10s0]"
	@echo >&2 " make unload [IF=enp10s0]"
	@echo >&2 ""

load:
	sudo ip link set dev ${IF} xdp obj program.o sec mysection

unload:
	sudo ip link set dev ${IF} xdp off

clean:
	rm -f program.o
