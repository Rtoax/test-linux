# SPDX-License-Identifier: GPL-3.0
target-bpf-y := classifier.bpf.o

target-post-y := help

IF := lo
$(warning "Specify IF=[Interface] like IF=lo")

include ../../../template/main.mk

help:
	@echo >&2 ""
	@echo >&2 " make"
	@echo >&2 " make   load [IF=enp10s0]"
	@echo >&2 " make unload [IF=enp10s0]"
	@echo >&2 ""

load: $(target-bpf-y)
	$(call log_tgt_exe,LOAD,,$(target-bpf-y))
	$(Q)sudo tc qdisc add dev ${IF} handle 0: ingress
	$(Q)sudo tc filter add dev ${IF} ingress bpf obj classifier.bpf.o flowid 0:

unload:
	$(call log_tgt_exe,UNLOAD,,$(target-bpf-y))
	@echo -e "  UNLOAD  \033[1mclassifier.bpf.o\033[m to \033[1m$(IF)\033[m"
	$(Q)sudo tc qdisc del dev ${IF} ingress
