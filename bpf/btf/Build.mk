# SPDX-License-Identifier: GPL-3.0
__USE_BTF_HELPERS__ = y

OUTPUT := .output/
subdir-y += btf_h
subdir-y += examples

include helpers.mk

target-liba-y := libbtf_helpers.a
target-libso-y := libbtf_helpers.so

target-y := btf_ksym
target-y += btf_kfunc
target-y += btf_struct
target-y += btf_decl_tag

libbtf_helpers.a-objs := ${OUTPUT}btf_helpers.a.o
libbtf_helpers.so-objs := ${OUTPUT}btf_helpers.so.o

btf_ksym-objs := ${BTF_HELPERS}
btf_kfunc-objs := ${BTF_HELPERS}
btf_struct-objs := ${BTF_HELPERS}
btf_decl_tag-objs := ${BTF_HELPERS}

LDFLAGS := -lbpf
CFLAGS_btf_kfunc := -DTEST_BTF_KIND_FUNC=1
CFLAGS_btf_struct := -DTEST_BTF_KIND_STRUCT=1
CFLAGS_btf_decl_tag := -DTEST_BTF_KIND_DECL_TAG=1
