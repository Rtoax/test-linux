# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/
subdir-y := examples

VMLINUX_H := vmlinux.h
target-prep-y := ${VMLINUX_H}

target-y := btf_ksym
target-y += btf_kfunc
target-y += btf_struct
target-y += btf_decl_tag

BTF_HELPERS := ${OUTPUT}btf_helpers.o

HELPERS := ${BTF_HELPERS}

LDFLAGS := -lbpf
CFLAGS_btf_kfunc := -DTEST_BTF_KIND_FUNC=1
CFLAGS_btf_struct := -DTEST_BTF_KIND_STRUCT=1
CFLAGS_btf_decl_tag := -DTEST_BTF_KIND_DECL_TAG=1

include ../../template/main.mk

${OUTPUT}btf_helpers.o: btf_helpers.h

btf_ksym: ${OUTPUT}btf_ksym.o ${HELPERS}
btf_kfunc: ${OUTPUT}btf_kfunc.o ${HELPERS}
btf_struct: ${OUTPUT}btf_struct.o ${HELPERS}
btf_decl_tag: ${OUTPUT}btf_decl_tag.o ${HELPERS}
