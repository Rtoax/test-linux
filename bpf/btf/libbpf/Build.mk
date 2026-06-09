# SPDX-License-Identifier: GPL-3.0
include helpers.mk

target-y += btf_dump
target-y += btf_info
target-y += btf_ksym

btf_dump-objs := ${BTF_HELPERS}
btf_ksym-objs := ${BTF_HELPERS}

LDFLAGS := -lbpf
