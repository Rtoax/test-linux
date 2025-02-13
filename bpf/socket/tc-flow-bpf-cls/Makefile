# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../../../tlbuild.mk

CLANG := clang

BPF_OBJ :=
BPF_OBJ += classifier.o

IF := lo
$(warning "Specify IF=[Interface] like IF=lo")

.PHONY: all
all: $(BPF_OBJ)
	@echo >&2 ""
	@echo >&2 " make"
	@echo >&2 " make   load [IF=enp10s0]"
	@echo >&2 " make unload [IF=enp10s0]"
	@echo >&2 ""

%.o: %.c
	@echo -e "  CLANG-K  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -O2 -Wall -target bpf -c $(<) -o $(@) ${CFLAGS_KERN}

load: $(BPF_OBJ)
	@echo -e "  LOAD  \033[1mclassifier.o\033[m to \033[1m$(IF)\033[m"
	$(Q)sudo tc qdisc add dev ${IF} handle 0: ingress
	$(Q)sudo tc filter add dev ${IF} ingress bpf obj classifier.o flowid 0:

unload:
	@echo -e "  UNLOAD  \033[1mclassifier.o\033[m to \033[1m$(IF)\033[m"
	$(Q)sudo tc qdisc del dev ${IF} ingress

clean:
	@echo -e "  RM  \033[1m$(BPF_OBJ)\033[m"
	$(Q)rm -f ${BPF_OBJ}
