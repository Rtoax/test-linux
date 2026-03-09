# SPDX-License-Identifier: GPL-3.0
__USE_BTF_HELPERS__ = y

OUTPUT := .output/
subdir-y := examples

target-liba-y := libbtf_helpers.a
target-libso-y := libbtf_helpers.so

target-y := btf_ksym
target-y += btf_kfunc
target-y += btf_struct
target-y += btf_decl_tag

ifneq ($(wildcard /sys/kernel/btf/kvm),)
  target-btf-y := kvm.h
endif

libbtf_helpers.a-objs := ${OUTPUT}btf_helpers.a.o
libbtf_helpers.so-objs := ${OUTPUT}btf_helpers.so.o

LDFLAGS := -lbpf
CFLAGS_btf_kfunc := -DTEST_BTF_KIND_FUNC=1
CFLAGS_btf_struct := -DTEST_BTF_KIND_STRUCT=1
CFLAGS_btf_decl_tag := -DTEST_BTF_KIND_DECL_TAG=1

include main.mk

${OUTPUT}btf_helpers.a.o: btf_helpers.h
${OUTPUT}btf_helpers.so.o: btf_helpers.h

btf_ksym: ${OUTPUT}btf_ksym.o ${BTF_HELPERS}
btf_kfunc: ${OUTPUT}btf_kfunc.o ${BTF_HELPERS}
btf_struct: ${OUTPUT}btf_struct.o ${BTF_HELPERS}
btf_decl_tag: ${OUTPUT}btf_decl_tag.o ${BTF_HELPERS}
