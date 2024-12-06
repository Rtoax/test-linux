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
	clang  -g -c -O2 -target bpf -c classifier.c -o classifier.o
	@echo >&2 ""
	@echo >&2 " make"
	@echo >&2 " make   load [IF=enp10s0]"
	@echo >&2 " make unload [IF=enp10s0]"
	@echo >&2 ""

load:
	sudo tc qdisc add dev ${IF} handle 0: ingress
	sudo tc filter add dev ${IF} ingress  bpf obj classifier.o flowid 0:

unload:
	sudo tc qdisc del dev ${IF} ingress

clean:
	rm -f *.o
