# SPDX-License-Identifier: GPL-3.0
include helpers.mk

subdir-y += btf_h
subdir-y += examples

target-y += btf_dump
target-y += btf_ksym
target-y += btf_kfunc
target-y += btf_struct
target-y += btf_decl_tag

btf_dump-objs := ${BTF_HELPERS}
btf_ksym-objs := ${BTF_HELPERS}
btf_kfunc-objs := ${BTF_HELPERS}
btf_struct-objs := ${BTF_HELPERS}
btf_decl_tag-objs := ${BTF_HELPERS}

LDFLAGS := -lbpf
CFLAGS_btf_kfunc := -DTEST_BTF_KIND_FUNC=1
CFLAGS_btf_struct := -DTEST_BTF_KIND_STRUCT=1
CFLAGS_btf_decl_tag := -DTEST_BTF_KIND_DECL_TAG=1
