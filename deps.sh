#!/bin/bash

pkgs=( make cmake gcc clang gdb )
pkgs+=( systemtap-sdt-devel )  # sdt.h
pkgs+=( libdwarf-tools )       # dwarfdump
pkgs+=( bpftrace bcc )         # eBPF

args=( --skip-broken )
args+=( --nogpgcheck )

sudo dnf install ${args[@]} -y ${pkgs[@]}
