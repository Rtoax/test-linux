# SPDX-License-Identifier: GPL-3.0
include btf.mk
OUTPUT := .output/
sub-dir := examples

TARGETS_PREP := vmlinux.h

TARGETS := btf_ksym
TARGETS += btf_kfunc
TARGETS += btf_decl_tag

BTF_HELPERS := ${OUTPUT}btf_helpers.o

HELPERS := ${BTF_HELPERS}

LDFLAGS := -lbpf
CFLAGS_btf_kfunc := -DTEST_BTF_KIND_FUNC=1
CFLAGS_btf_decl_tag := -DTEST_BTF_KIND_DECL_TAG=1

include ../../template/main.mk

include ../bpftool/vmlinux.h.mk

${OUTPUT}btf_helpers.o: btf_helpers.h

btf_ksym: ${OUTPUT}btf_ksym.o ${HELPERS}
btf_kfunc: ${OUTPUT}btf_kfunc.o ${HELPERS}
btf_decl_tag: ${OUTPUT}btf_decl_tag.o ${HELPERS}
