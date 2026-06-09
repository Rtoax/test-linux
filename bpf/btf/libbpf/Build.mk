# SPDX-License-Identifier: GPL-3.0
include helpers.mk

target-y += btf_dump
target-y += btf_info
target-y += btf_ksym

btf_dump-objs := ${BTF_HELPERS}
btf_ksym-objs := ${BTF_HELPERS}

prog-y += btf_dump
prog-y += btf_dump.1
prog-y += btf_dump.2

prog-y += btf_ksym
prog-y += btf_ksym.1
prog-y += btf_ksym.2
prog-y += btf_ksym.3

PROG_ARGS_btf_dump.1 := struct=file
PROG_ARGS_btf_dump.2 := struct=ALL

PROG_ARGS_btf_ksym := vfs_read
PROG_ARGS_btf_ksym.1 := func=vfs_write
PROG_ARGS_btf_ksym.2 := struct=file
PROG_ARGS_btf_ksym.3 := decl-tag=bpf_kfunc

LDFLAGS := -lbpf
